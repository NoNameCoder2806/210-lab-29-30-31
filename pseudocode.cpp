// COMSC-210 | Lab 29 | Dat Hoang Vien
// IDE used: Visual Studio Code

// Include necessary libraries and headers for file handling, data structures, etc.

// Define functions to simulate random events over time
    // Parameters: map of prehistoric time periods, number of intervals

// Define main function
    // Initialize a map to store the prehistoric time periods information, each associated with an array of lists for land, sea, and air creatures.

    // Open an external file to read initial data about each time periods and populate the map
        // If the file does not open, print an error and exit

    // Read the data from the file and populate the map
        // For each line, extract the time periods and creatures
        // Insert creatures into the appropriate list in the array depending on their type (land, sea, air)

    // Close the file

    // Being a time-based simulation for environmental changes
        // For 30 time intervals
            // Iterate through each prehistoric time period in the map
                // For each time period, simulate changes
                    // Randomly decide the number of species to add or remove from each category (land, sea, air)
                        // If adding, select a new species name to add to the list
                        // If removing, select a random species from the list to remove
                    //Print the changes for this interval, e.g., "Added {species} to {category} in {prehistoric time period}"

                // Simulate more complex environmental changes
                // Randomly decide if disasters and disease will happen

                // Wait or pause briefly to simulate the passage of time between intervals
// End of main function