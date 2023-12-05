import csv
import sys

def main():
    #Check for command-line usage
    if len(sys.argv) < 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    #Read database file into a variable
    database = []
    try:
        with open (sys.argv[1], 'r') as csvfile:
            csvfile_reader = csv.DictReader(csvfile)
            for i in csvfile_reader:
                database.append(i)
    except FileNotFoundError:
        print(f"Error: file {sys.argv[1]} not found")
        sys.exit(1)

    #Read DNA sequence file into a variable
    try:
        with open (sys.argv[2], 'r') as txtfile:
            dna_sequence = txtfile.read()
    except FileNotFoundError:
        print(f"Error: file {sys.argv[1]} not found")
        sys.exit(1)

    #List of subsequences to check
    subsequences = list(database[0].keys())[1:]

    #Find longest match of each STR in DNA sequence
    result = {}
    for subsequence in subsequences:
        result[subsequence] = longest_match(dna_sequence, subsequence)

    #Check database for matching profiles
    match_found = False
    for person in database:
        match = 0
        for subsequence in subsequences:
            if int(person[subsequence]) == result[subsequence]:
                match += 1
        if match == len(subsequences):
            print(person['name'])
            match_found = True

    if match_found == False:
        print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
