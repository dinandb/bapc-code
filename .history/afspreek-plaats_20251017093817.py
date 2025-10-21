import math

def geographic_mean(coords):
    """
    Compute the geographic mean (on a sphere) of 3 coordinates.
    coords: list of (longitude, latitude) in degrees
    returns: (mean_longitude, mean_latitude) in degrees
    """
    if len(coords) != 3:
        raise ValueError("Please provide exactly three coordinates.")
    
    # Convert each coordinate to radians and then to 3D Cartesian
    x = y = z = 0
    for lon_deg, lat_deg in coords:
        lon = math.radians(lon_deg)
        lat = math.radians(lat_deg)
        
        x += math.cos(lat) * math.cos(lon)
        y += math.cos(lat) * math.sin(lon)
        z += math.sin(lat)
    
    # Compute average Cartesian coordinate
    x /= 3
    y /= 3
    z /= 3

    # Convert back to longitude/latitude
    lon_mean = math.atan2(y, x)
    hyp = math.sqrt(x * x + y * y)
    lat_mean = math.atan2(z, hyp)
    
    # Convert back to degrees
    return (math.degrees(lon_mean), math.degrees(lat_mean))


# Example usage
coordinates = [
    (51.98736758169431, 5.928458504369204),  # ergens in arnhem noord
    (2.352222, 48.856613),  # Paris
    (13.4050, 52.5200)      # Berlin
]

mean_point = geographic_mean(coordinates)
print("Geographic mean (longitude, latitude):", mean_point)
