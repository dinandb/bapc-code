import pandas as pd


def get_data():
    """
    Load training data.
    """
    df = pd.read_excel("aangepaste_data/wedstrijdhistorie_training.xlsx")
    df.columns = [col.strip().lower() for col in df.columns]
    return df


def get_evaluation_data():
    """
    Load evaluation data.
    """
    df = pd.read_excel("aangepaste_data/wedstrijdhistorie_evaluatie.xlsx")
    df.columns = [col.strip().lower() for col in df.columns]
    return df


def get_team_average_goals(df, team):
    """
    Average goals scored by a team over all matches.
    """

    home_matches = df[df["thuis_team"] == team]
    away_matches = df[df["uit_team"] == team]

    goals = []

    goals.extend(home_matches["thuis_goals"].tolist())
    goals.extend(away_matches["uit_goals"].tolist())

    if len(goals) == 0:
        return 0

    return sum(goals) / len(goals)


def predict(team_a, team_b, training_df):
    """
    Predict goals for team_a and team_b.
    """

    # Find direct matches
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

    # Use head-to-head averages if available
    if not matches.empty:

        team_a_goals = []
        team_b_goals = []

        for _, match in matches.iterrows():

            if match["thuis_team"] == team_a:
                team_a_goals.append(match["thuis_goals"])
                team_b_goals.append(match["uit_goals"])

            else:
                team_a_goals.append(match["uit_goals"])
                team_b_goals.append(match["thuis_goals"])

        pred_a = sum(team_a_goals) / len(team_a_goals)
        pred_b = sum(team_b_goals) / len(team_b_goals)

    else:
        # Fallback: overall team averages
        pred_a = get_team_average_goals(training_df, team_a)
        pred_b = get_team_average_goals(training_df, team_b)

    return round(pred_a), round(pred_b)


def calculate_score(real_home, real_away, pred_home, pred_away):
    """
    Calculate score according to the provided puntentelling.
    """

    total_score = 0

    # ---------------------------------------------------
    # 1. Match outcome (win/draw/loss)
    # ---------------------------------------------------

    real_diff = real_home - real_away
    pred_diff = pred_home - pred_away

    if (
        (real_diff > 0 and pred_diff > 0) or
        (real_diff < 0 and pred_diff < 0) or
        (real_diff == 0 and pred_diff == 0)
    ):
        outcome_points = 10
    else:
        outcome_points = 0

    # ---------------------------------------------------
    # 2. Total goals
    # ---------------------------------------------------

    real_total = real_home + real_away
    pred_total = pred_home + pred_away

    total_goals_points = max(
        0,
        10 - (real_total - pred_total) ** 2
    )

    # ---------------------------------------------------
    # 3. Goal difference
    # ---------------------------------------------------

    goal_diff_points = max(
        0,
        10 - abs(real_diff - pred_diff)
    )

    total_score = (
        outcome_points +
        total_goals_points +
        goal_diff_points
    )

    return {
        "outcome_points": outcome_points,
        "total_goals_points": total_goals_points,
        "goal_diff_points": goal_diff_points,
        "total_score": total_score
    }


def evaluate():
    """
    Evaluate all matches in the evaluation dataset.
    """

    training_df = get_data()
    eval_df = get_evaluation_data()

    results = []

    total_points = 0

    for _, row in eval_df.iterrows():

        team_a = row["thuis_team"]
        team_b = row["uit_team"]

        real_home = row["thuis_goals"]
        real_away = row["uit_goals"]

        pred_home, pred_away = predict(
            team_a,
            team_b,
            training_df
        )

        score = calculate_score(
            real_home,
            real_away,
            pred_home,
            pred_away
        )

        total_points += score["total_score"]

        results.append({
            "thuis_team": team_a,
            "uit_team": team_b,
            "real_score": f"{real_home}-{real_away}",
            "predicted_score": f"{pred_home}-{pred_away}",
            "match_points": score["total_score"]
        })

    results_df = pd.DataFrame(results)

    print(results_df)

    print("\n===================================")
    print(f"TOTAL SCORE: {total_points}")
    print(f"AVERAGE SCORE PER MATCH: {total_points / len(results_df):.2f}")
    print("===================================")

    return results_df


# Run evaluation
evaluate()