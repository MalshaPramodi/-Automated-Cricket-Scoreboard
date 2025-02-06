#include<iostream>
#include<iomanip>
#include<string>
#include "CricketScoreboard.h"
using namespace std;

CricketScoreboard::CricketScoreboard() {            ///Constructor
    teamAScore = 0;                                 ///Initialize Member variables
    teamAWickets = 0;
    teamBScore = 0;
    teamBWickets = 0;
    target = 0;
    remainingOvers = 0;
    ballsFacedA = 0;
    ballsFacedB = 0;
    finalTeamAScore = 0;
    finalTeamBScore = 0;
    totalWicketsA = 0;
    totalWicketsB = 0;
    currentRunRateA = 0.0;
    currentRunRateB = 0.0;
    scoreWithoutExtraA = 0;
    scoreWithoutExtraB = 0;
    inningOver = false;

   // Initialize arrays for each over 
    for (int i = 0; i < 20; i++) {
        runsInOverA[i] = 0;
        runsInOverB[i] = 0;
        wicketsInOverA[i] = 0;
        wicketsInOverB[i] = 0;
        noBallsInOverA[i] = 0;
        noBallsInOverB[i] = 0;
        widesInOverA[i] = 0;
        widesInOverB[i] = 0;
        foursInOverA[i] = 0;
        sixesInOverA[i] = 0;
        foursInOverB[i] = 0;
        sixesInOverB[i] = 0;
    }
}

/// Function to display the score for a ball
void CricketScoreboard::displayScore(int runsScored, const string& teamName, int over, int ball, bool isWide, bool isNoBall) {
    cout << "Ball" << ball << " (Over " << over << ", " << teamName << "): " << runsScored << " runs" << endl;
    if (isWide) {
        cout << "** WIDE BALL **" << endl;
        cout << endl;
    }
}

/// Display the current score at the end of an over
void CricketScoreboard::displayTeamScore(int runs, int wickets, const string& teamName, int overs) {
    cout << "Team " << teamName << ": " << runs << "/" << wickets << " (" << overs << " overs)" << endl;
    cout << endl<<endl;
}

/// Simulate the process of one over for a team
void CricketScoreboard::simulateOver(const string& teamName) {
    for (int over = 1; over <= 20; over++) {      ///Simulate for 20 overs
        for (int ball = 1; ball <= 6; ball++) {  /// For 6 deliveries in an over

            int runsScored;

            bool isWide = false;
            bool isNoBall = false;
  

              /// Simulate wide or no ball (occurs with a certain probability)
            if (rand() % 20 == 0) {    ///5% chance of wide ball occurring
                isWide = true;
                runsScored = 1;      /// Runs scored for a wide ball is 1
                if (teamName == "A") {
                    widesInOverA[over - 1]++;       //Get the count of the no. of wides
                }
                else {
                    widesInOverB[over - 1]++;
                }
            }
            else if (rand() % 30 == 0) { ///3.33% chance of no ball occurring
                isNoBall = true;
                int noBallScore = 1;     /// Add an extra 1 run to the score in a no ball occurring according to the rules in cricket

                int possibleScore[] = { 0,1,2,3,4,6 };

                //Selecting a random index to select a score from the array
                int randIndex = rand() % 6;   //Generate index values from 0 to 5 with a probability of 16.67%

                                                 
                int FreeHitScore = possibleScore[randIndex];
                runsScored = noBallScore + FreeHitScore; //Total runs scored for the No Ball

                cout << "No Ball: " << noBallScore << endl;
                cout << "Free Hit: " << FreeHitScore << endl;               
               
                if (teamName == "A") {               //Get the count of no balls in each over
                    noBallsInOverA[over - 1]++;
                }
                else {
                    noBallsInOverB[over - 1]++;
                }
            }
            else if (rand() % 10 == 0) {       /// Random probability for a wicket is 10%
                runsScored = 0;
                cout << "WICKET!" << endl;
                if (teamName == "A") {
                    teamAWickets++;
                    wicketsInOverA[over - 1]++;
                }
                else {
                    teamBWickets++;
                    wicketsInOverB[over - 1]++;
                }
            }

            else {
                //Array for possible runscores to ommit the score of 5
                int possibleScore[] = { 0,0,1,0,1,2,0,3,2,4,6 };

                //Selecting a random index to select a score from the array
                int randIndex = rand() % 11;   //Generate index values from 0 to 10 randomly
                runsScored = possibleScore[randIndex]; // Regular runs (0 to 6 runs)

                if (runsScored == 4) {               //Get the count of 4s in an over
                    if (teamName == "A") {
                        foursInOverA[over - 1]++;
                    }
                    else {
                        foursInOverB[over - 1]++;
                    }
                }
                else if (runsScored == 6) {       //Get the count of sixes in an over
                    if (teamName == "A") {
                        sixesInOverA[over - 1]++;
                    }
                    else {
                        sixesInOverB[over - 1]++;
                    }
                }
            }


            // Update the legal ball count and runs scored for the respective team
            if (!isWide && !isNoBall) {
                if (teamName == "A") {                  
                    scoreWithoutExtraA += runsScored;
                    ballsFacedA++;
                }
                else {
                    scoreWithoutExtraB += runsScored;
                    ballsFacedB++;
                }
            }

            if (firstToBat == "A") {
                if (teamName == "A") { ///Update the score for the corresponding team
                    teamAScore += runsScored;
                    runsInOverA[over - 1] += runsScored; // Record runs scored in this over for Team A
                    displayScore(runsScored, "A", over, ball, isWide, isNoBall);
                }

                else if (teamBScore < target) {
                    teamBScore += runsScored;
                    runsInOverB[over - 1] += runsScored; // Record runs scored in this over for Team B
                    displayScore(runsScored, "B", over, ball, isWide, isNoBall);
                }
                else {
                    if (teamBScore >= target) {      //if teamBScore >= target, the match should be over
                        inningOver = true;
                        break;
                    }
                }
            }
            else if (firstToBat == "B") {
                if (teamName == "B") {                   //Update the score for the corresponding team
                    teamBScore += runsScored;
                    runsInOverB[over - 1] += runsScored;  // Record runs scored in this over for Team A
                    displayScore(runsScored, "B", over, ball, isWide, isNoBall);
                }

                else if (teamAScore < target) {
                    teamAScore += runsScored;
                    runsInOverA[over - 1] += runsScored;  // Record runs scored in this over for Team B
                    displayScore(runsScored, "A", over, ball, isWide, isNoBall);
                }
                else {
                    if (teamAScore >= target) {       //if teamBScore >= target, the match should be over
                        inningOver = true;
                        break;
                    }
                }
            }

            if (!isWide && !isNoBall) {
            if (teamName == "A") {
                currentRunRateA = static_cast<double>(scoreWithoutExtraA) / (ballsFacedA / 6.0);
                cout << "Current Run Rate (Team A): " << fixed << setprecision(2) << currentRunRateA << endl;
                cout << endl;
            }

            else {
                currentRunRateB = static_cast<double>(teamBScore) / (ballsFacedB / 6.0);
                cout << "Current Run Rate (Team B): " << fixed << setprecision(2) << currentRunRateB << endl;
                cout << endl;
            }
            }

            // Other conditions to end the match
            if (inningOver || teamAWickets >= 10 || teamBWickets >= 10) {

                inningOver = true;
                break;
            }
        }

        if (inningOver) {      // Check whether the inning is over
            break;
        }

        ///Function to display the current score of the team
        displayTeamScore((teamName == "A") ? teamAScore : teamBScore, (teamName == "A") ? teamAWickets : teamBWickets, teamName, over);
        if (over == 0)     /// The total target is displayed at the beginning
        {
            cout << "Target: " << target << endl;
        }
        else     /// Calculate the target according to the score in each over
        {
            if (teamAScore < target || teamBScore < target) {
                cout << "Target: " << ((firstToBat == "A") ? target - teamBScore : target - teamAScore);
                cout << endl;
            }
        }
        if (firstToBall == "B" || firstToBall == "A") {
            remainingOvers = 20 - over; /// Update the remaining overs for the batting Team in the second inning  
            calculateRequiredRunRate();
        }

    }
}    // End of the simulateOver function

/// Function to calculate required run rate
void CricketScoreboard::calculateRequiredRunRate() {
    if (firstToBall == "B") {
        if (teamBScore < target && remainingOvers > 0) {
            double requiredRunRate = static_cast<double>(target - teamBScore) / remainingOvers;
            cout << "Required Run Rate for Team B to win: " << fixed << setprecision(2) << requiredRunRate << endl;
            cout << endl;
        }
    }
    else if (firstToBall == "A") {
        if (teamAScore < target && remainingOvers > 0) {
            double requiredRunRate = static_cast<double>(target - teamAScore) / remainingOvers;
            cout << "Required Run Rate for Team A to win: " << fixed << setprecision(2) << requiredRunRate << endl;
            cout << endl;
        }
    }

}


///Function to begin the Match
void CricketScoreboard::startMatch() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "\n------------------- T20 Cricket Match: Team A vs. Team B--------------\n" << endl;
    /// 20 overs per inning

     ///Toss the coin first.
     ///Generate a random number(0 or 1)
    int tossResult = rand() % 2;     ///Probability of toss result getting either head or tail is 50%

    tossWinTeam = (tossResult == 1) ? "A" : "B";
    string winningDecision;

    cout << "Team " << tossWinTeam << " won the toss and chose to (bat/bowl) first: ";
    cin >> winningDecision;
    cout << endl;

    /// Selecting which team to bat first and ball first according to the toss result
    if (tossWinTeam == "A") {
        if (winningDecision == "bat" || winningDecision == "BAT") {
            firstToBat = "A";
            firstToBall = "B";
        }
        else if (winningDecision == "bowl" || winningDecision == "BOWL") {
            firstToBat = "B";
            firstToBall = "A";
        }
        else {
            cout << "Invalid input! Please use either only lowercase or uppercase letters." << endl;
            exit(EXIT_FAILURE);
        }
    }
    else if (tossWinTeam == "B") {  //if the toss win team is B
        if (winningDecision == "bat" || winningDecision == "BAT") {
            firstToBat = "B";
            firstToBall = "A";
        }
        else if (winningDecision == "bowl" || winningDecision == "BOWL") {
                firstToBat = "A";
                firstToBall = "B";
        }
        else {
            cout << "Invalid input! Please use either only lowercase or uppercase letters." << endl;
            exit(EXIT_FAILURE);
        }
    }

    //First team to bat
    simulateOver(firstToBat);
    displayFinalScore(firstToBat);

    //Update the target based on the the team which bat first
    target = (firstToBat == "A") ? teamAScore + 1 : teamBScore + 1;


    if (firstToBat == "A") {
        finalTeamAScore = teamAScore;    //Store the values before other Team statrts Batting
        totalWicketsA = teamAWickets;
    }
    else if (firstToBat == "B") {
        finalTeamBScore = teamBScore;    //Store the values before other Team statrts Batting
        totalWicketsB = teamBWickets;
    }

    cout << endl << "Target for Team " << firstToBall << " is " << target << endl;
    cout << endl;

    //Reset the values to begin the second round
    inningOver = false;

    if (firstToBat == "A") {
        teamAScore = 0;    //Store the values before other Team statrting Batting
        teamAWickets = 0;
    }
    else if (firstToBat == "B") {
        teamBScore = 0;    //Store the values before other Team statrting Batting
        teamBWickets = 0;
    }


    //srand(static_cast<unsigned int>(time(nullptr)));

    //Batting team in the second inning
    simulateOver(firstToBall);

    //Display Team's final score in the second inning
    displayFinalScore(firstToBall);

    //Determine the winning team at the end
    determineMatchResult();
}
////////////////End of startMatch function

///Function to display final score of a team
void CricketScoreboard::displayFinalScore(const string& teamName) {
    cout << endl << "---------------------------------------------------------------------------" << endl;
    cout << endl << "Inning over! Final score for Team " << teamName << ": " << ((teamName == "A") ? teamAScore : teamBScore) << "/" << ((teamName == "A") ? teamAWickets : teamBWickets) << endl;
    cout << endl << "---------------------------------------------------------------------------" << endl;
}

///Function to determine the winning team 
void CricketScoreboard::determineMatchResult() {
    if (firstToBat == "A") {
        if (teamBScore >= target) {
            cout << "\nTeam B won the match by " << (teamBScore - target + 1) << " runs and " << (10 - teamBWickets) << " wickets!" << endl;
        }
        else if (teamBScore == target - 1) {
            cout << "\nIt's a tie!" << endl;
        }
        else {
            cout << "\nTeam A won the match by " << (target - teamBScore - 1) << " runs and " << (10 - totalWicketsA) << " wickets!" << endl;
        }
        /// Store final scores and wickets
        finalTeamBScore = teamBScore;
        totalWicketsB = teamBWickets;
    }
    else if (firstToBat == "B") {
        if (teamAScore >= target) {
            cout << "\nTeam A won the match by " << (teamAScore - target + 1) << " runs and " << (10 - teamAWickets) << " wickets!" << endl;
        }
        else if (teamAScore == target - 1) {
            cout << "\nIt's a tie!" << endl;
        }
        else {
            cout << "\nTeam B won the match by " << (target - teamAScore - 1) << " runs and " << (10 - totalWicketsB) << " wickets!" << endl;
        }
        // Store final scores and wickets
        finalTeamAScore = teamAScore;
        totalWicketsA = teamAWickets;
    }
}

/// Function to view detailed scorecard
void CricketScoreboard:: displayDetailedScorecard() {
    cout << "\nDetailed Scorecard:" << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << setw(5) << "Over" << setw(15) << "Team A" << setw(10) << "Fours" << setw(10) << "Sixes" << setw(15)
        << "Team B" << setw(10) << "Fours" << setw(10) << "Sixes" << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < 20; i++) {
        cout << setw(5) << i + 1 << setw(10) << runsInOverA[i] << " runs" << setw(10) << foursInOverA[i] << setw(10) << sixesInOverA[i] << setw(10)
            << runsInOverB[i] << " runs" << setw(10) << foursInOverB[i] << setw(10) << sixesInOverB[i] << setw(10) << endl;
    }
}

///Function to view Bowling Scorecard
void CricketScoreboard::displayBowlingScorecard() {
    cout << "\nBowling Scorecard" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Team B Bowling Score card" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "\n" << setw(5) << "Over" << setw(15) << "Wickets" << setw(10) << "Wides" << setw(12) << "No Balls" << endl;
    cout << "-----------------------------------------" << endl;
    for (int i = 0; i < 20; i++) {
        cout << setw(5) << i + 1 << setw(10) << wicketsInOverA[i] << setw(12) << widesInOverA[i] << setw(10) << noBallsInOverA[i] << endl;

    }
    cout << "\n\nTeam A Bowling Score card" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "\n" << setw(5) << "Over" << setw(15) << "Wickets" << setw(10) << "Wides" << setw(12) << "No Balls" << endl;
    cout << "-----------------------------------------" << endl;
    for (int i = 0; i < 20; i++) {
        cout << setw(5) << i + 1 << setw(10) << wicketsInOverB[i] << setw(12) << widesInOverB[i] << setw(10) << noBallsInOverB[i] << endl;
    }
}

///Function to display the Menu List
void CricketScoreboard::showMenu() {
    int choice;
    bool exitMenu = false;

    while (!exitMenu) {
        cout << "\nMenu Options:" << endl;
        cout << "1. View Match Result" << endl;
        cout << "2. View Detailed Scorecard" << endl;
        cout << "3. View Bawling Scorecard" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\n Match Results" << endl;
            cout << setw(12) << "Team A" << setw(12) << "Team B" << endl;
            cout << setw(10) << finalTeamAScore << "/" << totalWicketsA << setw(10) << finalTeamBScore << "/" << totalWicketsB << endl;
            determineMatchResult(); /// Call the function to display match result
            break;
        case 2:
            /// Call a function to display a detailed scorecard
            displayDetailedScorecard();
            break;
        case 3:
            displayBowlingScorecard();
            break;
        case 4:
            exitMenu = true; /// Exit the menu loop
            break;
        default:
            cout << "Invalid choice. Please enter a valid option (1-3)." << endl;
            break;
        }
    }
}

