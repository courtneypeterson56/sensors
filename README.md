# sensors
This program simulates the notion of several "distributed" temperature sensors that feed data to a single source. Each sensor (really a thread) is responsible for updating a place in a linked list of temperatures initialized by the parent program (the single source).
