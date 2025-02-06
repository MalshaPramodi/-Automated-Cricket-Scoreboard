class CricketScoreboard {
private:
    std::string tossWinTeam;
    std::string firstToBat, firstToBall;
    int teamAScore;
    int teamAWickets;
    int teamBScore;
    int teamBWickets;
    int target;
    int remainingOvers;
    int ballsFacedA;
    int ballsFacedB;
    int runsInOverA[20];    //Keep the track of the runs in each over
    int runsInOverB[20];
    int finalTeamAScore;   //Final score of each team
    int finalTeamBScore;
    int totalWicketsA;
    int totalWicketsB;
    int wicketsInOverA[20]; // Keep the track of wickets in each over 
    int wicketsInOverB[20];
    int noBallsInOverA[20]; // Keep the track of no balls in each over 
    int noBallsInOverB[20];
    int widesInOverA[20];   // Keep the track of wides in each over 
    int widesInOverB[20];
    int foursInOverA[20];   //Keep the track of boundaries in each over
    int sixesInOverA[20];
    int foursInOverB[20];
    int sixesInOverB[20];
    double currentRunRateA;
    double currentRunRateB;
    int scoreWithoutExtraA;
    int scoreWithoutExtraB;
    bool inningOver;

public:
    CricketScoreboard();
    void displayScore(int runsScored, const std:: string& teamName, int over, int ball, bool isWide, bool isNoBall);
    void displayTeamScore(int runs, int wickets, const std::string& teamName, int overs);
    void simulateOver(const std::string& teamName);
    void calculateRequiredRunRate();
    void startMatch();
    void displayFinalScore(const std::string& teamName);
    void determineMatchResult();
    void displayDetailedScorecard();
    void displayBowlingScorecard();
    void showMenu();
};