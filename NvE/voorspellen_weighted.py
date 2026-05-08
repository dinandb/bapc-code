import math
import pandas as pd


DECAY_RATE = 0.5
ALPHA = 0.5


def get_data():
    df = pd.read_excel("aangepaste_data/wedstrijdhistorie.xlsx")
    df.columns = [col.strip().lower() for col in df.columns]
    return df


def get_round_data():
    df = pd.read_excel("antwoord/ronde1.xlsx")
    df.columns = [col.strip().lower() for col in df.columns]
    return df


def calculate_weights(years, pred_year):
    years_ago = pred_year - years

    raw_weights = years_ago.apply(
        lambda y: math.exp(-DECAY_RATE * y)
    )

    return raw_weights / raw_weights.sum()


def weighted_average(values, weights):
    return (values * weights).sum()


def precompute_team_averages(training_df, evaluation_years):
    team_averages = {}

    teams = set(training_df["thuis_team"]).union(set(training_df["uit_team"]))

    for pred_year in evaluation_years:
        team_averages[pred_year] = {}

        for team in teams:

            home = training_df[training_df["thuis_team"] == team]
            away = training_df[training_df["uit_team"] == team]

            goals = []
            years = []

            for _, r in home.iterrows():
                goals.append(r["thuis_goals"])
                years.append(r["jaar"])

            for _, r in away.iterrows():
                goals.append(r["uit_goals"])
                years.append(r["jaar"])

            if len(goals) == 0:
                avg = 0
            else:
                goals = pd.Series(goals)
                years = pd.Series(years)

                if DECAY_RATE == 0:
                    avg = goals.mean()
                else:
                    weights = calculate_weights(years, pred_year)
                    avg = weighted_average(goals, weights)

            team_averages[pred_year][team] = avg

    return team_averages


def predict(team_a, team_b, training_df, pred_year, team_averages):

    overall_a = team_averages[pred_year].get(team_a, 0)
    overall_b = team_averages[pred_year].get(team_b, 0)

    matches = training_df[
        (
            (training_df["thuis_team"] == team_a) &
            (training_df["uit_team"] == team_b)
        ) |
        (
            (training_df["thuis_team"] == team_b) &
            (training_df["uit_team"] == team_a)
        )
    ]

    if matches.empty:
        return round(overall_a), round(overall_b)

    a_goals, b_goals, years = [], [], []

    for _, m in matches.iterrows():

        if m["thuis_team"] == team_a:
            a_goals.append(m["thuis_goals"])
            b_goals.append(m["uit_goals"])
        else:
            a_goals.append(m["uit_goals"])
            b_goals.append(m["thuis_goals"])

        years.append(m["jaar"])

    a_goals = pd.Series(a_goals)
    b_goals = pd.Series(b_goals)
    years = pd.Series(years)

    if DECAY_RATE == 0:
        h2h_a = a_goals.mean()
        h2h_b = b_goals.mean()
    else:
        weights = calculate_weights(years, pred_year)
        h2h_a = weighted_average(a_goals, weights)
        h2h_b = weighted_average(b_goals, weights)

    pred_a = ALPHA * h2h_a + (1 - ALPHA) * overall_a
    pred_b = ALPHA * h2h_b + (1 - ALPHA) * overall_b

    return round(pred_a), round(pred_b)


def predict_round():
    training_df = get_data()
    round_df = get_round_data()

    years = [2016]  # or derive from data if needed

    team_averages = precompute_team_averages(training_df, years)

    predictions_a = []
    predictions_b = []

    for _, row in round_df.iterrows():

        team_a = row["team 1"] if "team 1" in row else row.iloc[0]
        team_b = row["team 2"] if "team 2" in row else row.iloc[1]

        pred_a, pred_b = predict(
            team_a,
            team_b,
            training_df,
            years[0],
            team_averages
        )

        predictions_a.append(pred_a)
        predictions_b.append(pred_b)

    round_df["Goals Team 1"] = predictions_a
    round_df["Goals Team 2"] = predictions_b

    round_df.to_excel("antwoord/ronde1_with_predictions.xlsx", index=False)

    return round_df


# Run
predict_round()