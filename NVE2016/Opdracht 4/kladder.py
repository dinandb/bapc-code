import pandas as pd
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
import csv
import math
import subprocess

df = pd.read_csv("cadeaus.csv")
X = df[["Breedtegraad", "Lengtegraad"]]

R = 6371
SOLUTIONS = []
SOLUTIONS2 = []

def bin_search(original_df, low, up):
    if low + 1 >= up:
        return 

    mid = (low + up) // 2

    new_df = original_df.copy()

    kmeans = KMeans(n_clusters=mid, random_state=42, n_init=10)
    new_df["Cluster"] = kmeans.fit_predict(X)
    all_valid = (new_df.groupby("Cluster")["Gewicht"].sum() <= 1000).all()

    if all_valid:
        SOLUTIONS.append(kmeans.labels_)

        return bin_search( original_df, low=low, up=mid )
    else:
        return bin_search( original_df, low=mid, up=up ) 

def total_search(original_df):
    new_df = original_df.copy()

    for k in range(1050, 949, -10):
        kmeans = KMeans(n_clusters=k, random_state=42, n_init=10)
        new_df["Cluster"] = kmeans.fit_predict(X)
        all_valid = (new_df.groupby("Cluster")["Gewicht"].sum() <= 1000).all()

        if all_valid:
            output_solution(kmeans.labels_)

            result = subprocess.run(
                [r".\CheckJeAntwoord.exe", "currentbest.csv"],
                capture_output=True,
                text=True
            )

            SOLUTIONS2.append((kmeans.labels_, result.stdout))
            print(f"iteration {k}, result={result.stdout}")
        else:
            break
    
def distance(row1, row2):
    phi_i = row1["Breedtegraad"]
    lambda_i = row1["Lengtegraad"]
    phi_j = row2["Breedtegraad"]
    lambda_j = row2["Lengtegraad"]

    d_lambda_rad = (lambda_i - lambda_j) * math.pi / 180
    phi_i_rad = phi_i * math.pi / 180
    phi_j_rad = phi_j * math.pi / 180

    dx = math.sin(phi_i_rad) - math.sin(phi_j_rad)
    dy = math.sin(d_lambda_rad) - math.cos(phi_i_rad)
    dz = math.cos(d_lambda_rad) * math.cos(phi_i_rad) - math.cos(phi_j_rad)

    return 2 * R * math.asin( math.sqrt(dx**2 + dy**2 + dz**2) / 2 )

def nearest_neighbor_tsp(group):
    group = group.copy().reset_index(drop=True)

    if len(group) <= 1:
        return group

    unvisited = list(group.index)

    # Start with the first cadeau in this trip
    current = unvisited.pop(0)
    order = [current]

    while unvisited:
        nearest = min(
            unvisited,
            key=lambda i: distance(group.loc[current], group.loc[i])
        )

        unvisited.remove(nearest)
        order.append(nearest)
        current = nearest

    return group.loc[order].reset_index(drop=True)

def output_solution(solution):
    df_with_trips = df.copy()
    df_with_trips["TripId"] = pd.Series(solution).values + 1

    ordered_trips = []

    for _, group in df_with_trips.groupby("TripId"):
        ordered_group = nearest_neighbor_tsp(group)
        ordered_trips.append(ordered_group)

    ordered_df = pd.concat(ordered_trips, ignore_index=True)

    output_df = ordered_df[["CadeauId", "TripId"]]

    output_df.to_csv("currentbest.csv", index=False)

def main():
    # bin_search(df, 1, 1000)
    total_search(df)
    SOLUTIONS2.sort(key=lambda x : x[1])

    # in csv
    print(f"Score is {SOLUTIONS2[0][1]}")
    output_solution(SOLUTIONS2[0][0])

main()