#include <iostream>
#include <cstdlib> // pentru system("clear")
#include <random>  // pentru scoruri aleatoare
#include <unordered_map> // pentru reclama
#include <exception> 
#include <vector> 
#include <algorithm> // pentru sortare+lambda
#include <string> // pentru string
#include <memory> // pentru smart pointers
using namespace std;



// Clasa pentru jucătorul de basket
class Player {
private:
    string name;
    int age;
    string position;
    static int totalPlayers;
public:
    Player(string name, int age, string position) {
        this->name = name;
        this->age = age;
        this->position = position;
        incrementTotalPlayers();
    }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getPosition() const { return position; }

    static int getTotalPlayers() {
        return totalPlayers;  // Metodă statică care returnează numărul total de jucători
    }

    static void incrementTotalPlayers() {
        totalPlayers++;  // Incrementarea numărului total de jucători
    }
protected:
    void displayPlayer() const {

        cout << name << " - " << age << " - " << position << endl;

    }

};

int Player::totalPlayers = 0;

// Clasa pentru jucătorul titular
class StartingPlayer : virtual public Player {
public:
    StartingPlayer(string name, int age, string position) : Player(name, age, position) {}
    // Metode și atribute specifice jucătorilor titulari
    void displayPlayer() const {
        Player::displayPlayer();
    }
};

// Clasa pentru jucătorul rezervă
class ReservePlayer : virtual public Player {
public:
    ReservePlayer(string name, int age, string position) : Player(name, age, position) {}
    // Metode și atribute specifice jucătorilor rezervă
    void displayPlayer() const {
        Player::displayPlayer();
    }
};

class Coach {
private:
    std::string name;

public:
    Coach(const std::string& name) : name(name) {}

    std::string getName() const {
        return name;
    }
};

// Clasa pentru echipa de baschet
class Team : public StartingPlayer, public ReservePlayer {
private:
    string name;
    vector<StartingPlayer*> startingPlayers; // Jucătorii titulari
    vector<ReservePlayer*> reservePlayers; // Jucătorii rezervă
    int wins;
    int losses;
    std::shared_ptr<Coach> coach;


public:
    Team(string name) : Player("", 0, ""), StartingPlayer("", 0, ""), ReservePlayer("", 0, "") {
        this->name = name;
        this->wins = 0;
        this->losses = 0;
    }

    string getName() const { return name; }
    int getWins() const { return wins; }
    int getLosses() const { return losses; }

    void setCoach(std::shared_ptr<Coach> coach) {
        this->coach = coach;
    }

    void addWin() { wins++; }
    void addLoss() { losses++; }

    void addStartingPlayer(StartingPlayer* player) {
        startingPlayers.push_back(player);
    }

    void addReservePlayer(ReservePlayer* player) {
        reservePlayers.push_back(player);
    }
    // Sortarea jucațorilor titulari după vârstă
    void sortStartingPlayersByAge() {
        sort(startingPlayers.begin(), startingPlayers.end(), [](const StartingPlayer* player1, const StartingPlayer* player2) {
            return player1->getAge() < player2->getAge();
            });
    }

    // Sortarea jucațorilor rezervă după vârstă
    void sortReservePlayersByAge() {
        sort(reservePlayers.begin(), reservePlayers.end(), [](const ReservePlayer* player1, const ReservePlayer* player2) {
            return player1->getAge() < player2->getAge();
            });
    }

    const vector<StartingPlayer*>& getStartingPlayers() const {
        return startingPlayers;
    }

    const vector<ReservePlayer*>& getReservePlayers() const {
        return reservePlayers;
    }

    int getNumStartingPlayers() const {
        return startingPlayers.size();
    }

    int getNumReservePlayers() const {
        return reservePlayers.size();
    }

    int getNumPlayers() const {
        return startingPlayers.size() + reservePlayers.size();
    }

    void displayAllPlayers() const {
        const vector<StartingPlayer*>& startingPlayers = getStartingPlayers();
        const vector<ReservePlayer*>& reservePlayers = getReservePlayers();
        cout << "Coach: " << coach->getName() << endl<<endl;
        cout << "All Players for team " << getName() << ":" << endl;

        for (const StartingPlayer* player : startingPlayers) {
            player->displayPlayer();
        }

        for (const ReservePlayer* player : reservePlayers) {
            player->displayPlayer();
            cout << " (Reserve)" << endl;
        }
    }

    void displayFirstFivePlayers() const {
        const vector<StartingPlayer*>& startingPlayers = getStartingPlayers();
        int numStartingPlayers = min(5, static_cast<int>(startingPlayers.size()));

        cout << "First Five Players for team " << getName() << ":" << endl;

        for (int i = 0; i < numStartingPlayers; i++) {
            const StartingPlayer* player = startingPlayers[i];
            player->displayPlayer();
        }
    }

    void displayReservePlayers() const {
        const vector<ReservePlayer*>& reservePlayers = getReservePlayers();

        cout << "Reserve Players for team " << getName() << ":" << endl;

        for (const ReservePlayer* player : reservePlayers) {
            player->displayPlayer();
            cout << " (Reserve)" << endl;
        }
    }

    bool operator==(const Team& other) const {
        return this->getName() == other.getName();
    }
};






// Clasa pentru meciul de basket
class Game {
protected:
    Team* team1;
    Team* team2;
    int score1;
    int score2;
    int team1ThreePointers;
    int team2ThreePointers;
    int team1Assists;
    int team2Assists;
    int team1Rebounds;
    int team2Rebounds;

public:
    Game(Team* team1, Team* team2) {
        this->team1 = team1;
        this->team2 = team2;
        score1 = 0;
        score2 = 0;
        team1ThreePointers = 0;
        team2ThreePointers = 0;
        team1Assists = 0;
        team2Assists = 0;
        team1Rebounds = 0;
        team2Rebounds = 0;
    }

    virtual ~Game() {
        // Nu este memorie alocată
    }

    Team* getTeam1() const { return team1; }
    Team* getTeam2() const { return team2; }
    int getScore1() const { return score1; }
    int getScore2() const { return score2; }
    void setScore1(int score) { score1 = score; }
    void setScore2(int score) { score2 = score; }

    virtual void updateWinLose() {
        if (score1 > score2) {
            team1->addWin();
            team2->addLoss();
        }
        else if (score2 > score1) {
            team2->addWin();
            team1->addLoss();
        }
    }



    virtual void displayStats() const = 0;

};

class GameStats : public Game {
public:
    GameStats(Team* team1, Team* team2) : Game(team1, team2) {}

    void updateStats() {
        // Actualizare statisticile jocului

        //  Incrementarea numărului de cosuri de 3 puncte pentru fiecare echipă
        team1ThreePointers += getRandomNumber();
        team2ThreePointers += getRandomNumber();

        //  Incrementarea numărului de assist-uri pentru fiecare echipă
        team1Assists += getRandomNumber();
        team2Assists += getRandomNumber();

        //  Incrementarea numărului de rebound-uri pentru fiecare echipă
        team1Rebounds += getRandomNumber();
        team2Rebounds += getRandomNumber();
    }

    void displayStats() const override {
        // Afisare statisticile de joc
        cout << "Game Statistics:" << endl;
        cout << "Team " << team1->getName() << " Three Pointers: " << team1ThreePointers << endl;
        cout << "Team " << team2->getName() << " Three Pointers: " << team2ThreePointers << endl;
        cout << "Team " << team1->getName() << " Assists: " << team1Assists << endl;
        cout << "Team " << team2->getName() << " Assists: " << team2Assists << endl;
        cout << "Team " << team1->getName() << " Rebounds: " << team1Rebounds << endl;
        cout << "Team " << team2->getName() << " Rebounds: " << team2Rebounds << endl;
    }


    int getRandomNumber() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(1, 10); // Intervalul în care se generează numărul

        return dist(gen);
    }
};


// Interfața pentru FanClub
class FanClub {
public:
    virtual ~FanClub() {}

    virtual void joinFanClub() const = 0;
    virtual void leaveFanClub() const = 0;
};

// Clasa TeamFanClub care implementează interfața FanClub
class TeamFanClub : public FanClub {
private:
    string teamName;

public:
    TeamFanClub(const string& teamName) : teamName(teamName) {}

    void joinFanClub() const override {
        cout << "You have joined the fan club of " << teamName << "." << endl;
    }

    void leaveFanClub() const override {
        cout << "You have left the fan club of " << teamName << "." << endl;
    }

    void celebrate() const {
        cout << "Fans of " << teamName << " are celebrating the victory!" << endl;
    }

    void contest() const {
        cout << "You are participating in a contest organized by the fan club of " << teamName << "." << endl;
    }
};

int fanClubMenu() {
    int choice;
    cout << "Fan Club Menu:" << endl;
    cout << "1. Celebrate" << endl;
    cout << "2. Contest" << endl;
    cout << "3. Leave Fan Club" << endl;
    cout << "4. Go back to the previous menu" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

void fanClubActions(TeamFanClub fanClub, bool& isFan) {
    int choice;
    isFan = true;
    do {
        choice = fanClubMenu();
        try {
            if (choice < 1 || choice > 5) {
                throw choice;
            }
        }
        catch (int choice) {
            cout << "Invalid choice" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
        }
        if (choice == 1)
        {
            fanClub.celebrate();
            system("pause");
            system("cls");

        }

        if (choice == 2) {
            fanClub.contest();
            system("pause");
            system("cls");

        }

        if (choice == 3) {

            isFan = false;
            fanClub.leaveFanClub();

        }

    } while (choice == 1 || choice == 2);

}


void displayTotalPlayers() {
    int totalPlayers = Player::getTotalPlayers();
    cout << "Total players: " << totalPlayers << endl;
}

// Clasa pentru turneul de basket
class Tournament {
private:
    string name;
    Game** games;
    int numGames;
    int maxGames;
    Team** teams;
    int numTeams;
    int maxTeams;
    string winner;
    static int totalPoints;
public:
    Tournament(string name, int maxTeams, int maxGames) {
        this->name = name;
        this->numTeams = 0;
        this->maxTeams = maxTeams;
        this->teams = new Team * [maxTeams];
        this->numGames = 0;
        this->maxGames = maxGames;
        this->games = new Game * [maxGames];
    }

    ~Tournament() {

        delete[] games;

        delete[] teams;
    }

    const string& getName() const {
        return name;
    }

    int getNumTeams() const {
        return numTeams;
    }

    int getNumGames() const {
        return numGames;
    }

    void setWinner(string winner) {
        this->winner = winner;
        system("pause");
        system("cls");
        cout << "The games are being procesed..." << endl;
    }

    string getWinner() {
        return winner;
    }

    bool addTeam(Team* team) {
        if (numTeams >= maxTeams) {
            return false;
        }
        teams[numTeams++] = team;
        return true;
    }

    bool addGame(Game* game) {
        if (numGames >= maxGames) {
            return false;
        }
        games[numGames++] = game;
        return true;
    }

    void afisareNumGames() {
        cout << "The number of games that are being played is: " << numGames << endl;
        displayTotalPlayers();
        cout << endl;
        system("pause");
    }

    const Team** getTeams() const {
        return (const Team**)teams;
    }

    const Game** getGames() const {
        return (const Game**)games;
    }

    static void addPoints(int points) {
        totalPoints += points;
    }

    static int getTotalPoints() {
        return totalPoints;
    }

    void play() {
        for (int i = 0; i < numGames; i++) {
            games[i]->updateWinLose();
        }
    }
};

int Tournament::totalPoints = 0;

// Afiseaza jucatorii unei echipe in functie de inputul din consola
void displayTeamPlayers(const Team& team) {
    cout << "Choose the player category to display:" << endl;
    cout << "1. All players" << endl;
    cout << "2. First 5 players" << endl;
    cout << "3. Reserves" << endl;
    int choice;
    cin >> choice;

    if (choice == 1) {
        team.displayAllPlayers();
    }
    else if (choice == 2) {
        team.displayFirstFivePlayers();
    }
    else if (choice == 3) {
        team.displayReservePlayers();
    }
    else {
        cout << "Invalid choice!" << endl;
    }
}



class NoMatchesException : public std::exception {
public:
    const char* what() const noexcept override {
        return "No matches found.";
    }
};



// Afiseaza meciuri jucate de o echipa
void showMatches(const string& teamName, const Tournament& tournament) {
    int numGames = tournament.getNumGames();
    bool foundMatches = false;
    for (int i = 0; i < numGames; i++) {
        const Game* game = tournament.getGames()[i];
        const Team* team1 = game->getTeam1();
        const Team* team2 = game->getTeam2();

        if ((team1->getName() == teamName) || (team2->getName() == teamName)) {
            foundMatches = true;
            cout << "Game " << i + 1 << ": " << team1->getName() << " vs " << team2->getName() << " - Final score: " << game->getScore1() << " - " << game->getScore2() << endl;
        }
    }
    if (!foundMatches) {
        throw NoMatchesException();
    }
}


class TeamFactory {
public:
    static Team* createTeam(const string& name) {
        Team* team = new Team(name);
        return team;
    }
};


class InvalidTeamException : public std::exception {
private:
    std::string message;

public:
    InvalidTeamException(const std::string& teamName) {
        message = "Invalid team: " + teamName;
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

template <typename T>
class ProfitCalculator {
public:
    float calculateProfit(const T& t) {
        // Implementarea generală (poți lăsa această metodă goală sau o poți suprascrie în specializările)
        return 0.0f;
    }
};

// Specializare pentru Team*
template <>
class ProfitCalculator<Team*> {
public:
    float calculateProfit(const Team* team) {
        int numWins = team->getWins();
        float profit = numWins * 10000;
        return profit;
    }
};

// Specializare pentru Tournament
template <>
class ProfitCalculator<Tournament> {
public:
    float calculateProfit(const Tournament& tournament) {
        // Profitul pentru un turneu este calculat în funcție de scorul total al tuturor meciurilor
        // Fiecare punct aduce un profit de 1000 unități

        int totalScore = 0;
        int numGames = tournament.getNumGames();
        const Game** games = tournament.getGames();
        for (int i = 0; i < numGames; i++) {
            totalScore += games[i]->getScore1() + games[i]->getScore2();
        }
        return totalScore * 100;
    }
};

// Lista de jucători si echipe

std::vector<Team*> teams;
using CoachPtr = std::shared_ptr<Coach>;


int main() {

    Team* lakers = TeamFactory::createTeam("Lakers");
    lakers->addStartingPlayer(new StartingPlayer(string("LeBron James"), 37, string("SF")));
    lakers->addStartingPlayer(new StartingPlayer(string("Anthony Davis"), 28, string("PF")));
    lakers->addStartingPlayer(new StartingPlayer(string("Russell Westbrook"), 33, string("PG")));
    lakers->addStartingPlayer(new StartingPlayer(string("Carmelo Anthony"), 37, string("SF")));
    lakers->addStartingPlayer(new StartingPlayer(string("Dwight Howard"), 36, string("C")));
    lakers->addReservePlayer(new ReservePlayer(string("Talen Horton-Tucker"), 20, string("SG")));
    lakers->addReservePlayer(new ReservePlayer(string("Kendrick Nunn"), 26, string("PG")));
    lakers->addReservePlayer(new ReservePlayer(string("Rajon Rondo"), 35, string("PG")));
    lakers->addReservePlayer(new ReservePlayer(string("Kent Bazemore"), 32, string("SG")));
    lakers->addReservePlayer(new ReservePlayer(string("D'Angelo Russell"), 27, string("PG")));

    lakers->sortStartingPlayersByAge();
    lakers->sortReservePlayersByAge();


    Team* clippers = TeamFactory::createTeam("Clippers");
    clippers->addStartingPlayer(new StartingPlayer(string("Kawhi Leonard"), 30, string("SF")));
    clippers->addStartingPlayer(new StartingPlayer(string("Paul George"), 31, string("SG")));
    clippers->addStartingPlayer(new StartingPlayer(string("Serge Ibaka"), 32, string("PF")));
    clippers->addStartingPlayer(new StartingPlayer(string("Reggie Jackson"), 31, string("PG")));
    clippers->addStartingPlayer(new StartingPlayer(string("Marcus Morris"), 32, string("PF")));
    clippers->addReservePlayer(new ReservePlayer(string("Luke Kennard"), 25, string("SG")));
    clippers->addReservePlayer(new ReservePlayer(string("Ivica Zubac"), 24, string("C")));
    clippers->addReservePlayer(new ReservePlayer(string("Terance Mann"), 24, string("SF")));
    clippers->addReservePlayer(new ReservePlayer(string("Nicolas Batum"), 33, string("SF")));
    clippers->addReservePlayer(new ReservePlayer(string("Rajon Rondo"), 35, string("PG")));

    clippers->sortStartingPlayersByAge();
    clippers->sortReservePlayersByAge();

    Team* bucks = TeamFactory::createTeam("Bucks");
    bucks->addStartingPlayer(new StartingPlayer(string("Giannis Antetokounmpo"), 26, string("PF")));
    bucks->addStartingPlayer(new StartingPlayer(string("Khris Middleton"), 30, string("SF")));
    bucks->addStartingPlayer(new StartingPlayer(string("Jrue Holiday"), 31, string("PG")));
    bucks->addStartingPlayer(new StartingPlayer(string("Brook Lopez"), 33, string("C")));
    bucks->addStartingPlayer(new StartingPlayer(string("Donte DiVincenzo"), 24, string("SG")));
    bucks->addReservePlayer(new ReservePlayer(string("Bobby Portis"), 26, string("PF")));
    bucks->addReservePlayer(new ReservePlayer(string("Pat Connaughton"), 28, string("SG")));
    bucks->addReservePlayer(new ReservePlayer(string("George Hill"), 35, string("PG")));
    bucks->addReservePlayer(new ReservePlayer(string("Rodions Kurucs"), 23, string("SF")));
    bucks->addReservePlayer(new ReservePlayer(string("Thanasis Antetokounmpo"), 29, string("SF")));

    bucks->sortStartingPlayersByAge();
    bucks->sortReservePlayersByAge();

    Team* nets = TeamFactory::createTeam("Nets");
    nets->addStartingPlayer(new StartingPlayer(string("Kevin Durant"), 33, string("SF")));
    nets->addStartingPlayer(new StartingPlayer(string("James Harden"), 32, string("SG")));
    nets->addStartingPlayer(new StartingPlayer(string("Kyrie Irving"), 29, string("PG")));
    nets->addStartingPlayer(new StartingPlayer(string("Blake Griffin"), 32, string("PF")));
    nets->addStartingPlayer(new StartingPlayer(string("LaMarcus Aldridge"), 36, string("C")));
    nets->addReservePlayer(new ReservePlayer(string("Joe Harris"), 30, string("SF")));
    nets->addReservePlayer(new ReservePlayer(string("Patty Mills"), 33, string("PG")));
    nets->addReservePlayer(new ReservePlayer(string("Bruce Brown"), 24, string("SG")));
    nets->addReservePlayer(new ReservePlayer(string("Paul Millsap"), 36, string("PF")));
    nets->addReservePlayer(new ReservePlayer(string("DeAndre' Bembry"), 27, string("SF")));

    nets->sortStartingPlayersByAge();
    nets->sortReservePlayersByAge();

    Team* sixers = TeamFactory::createTeam("Sixers");
    sixers->addStartingPlayer(new StartingPlayer(string("Joel Embiid"), 27, string("C")));
    sixers->addStartingPlayer(new StartingPlayer(string("Tobias Harris"), 29, string("PF")));
    sixers->addStartingPlayer(new StartingPlayer(string("Ben Simmons"), 25, string("PG")));
    sixers->addStartingPlayer(new StartingPlayer(string("Seth Curry"), 31, string("SG")));
    sixers->addStartingPlayer(new StartingPlayer(string("Danny Green"), 34, string("SF")));
    sixers->addReservePlayer(new ReservePlayer(string("Andre Drummond"), 28, string("C")));
    sixers->addReservePlayer(new ReservePlayer(string("George Hill"), 35, string("PG")));
    sixers->addReservePlayer(new ReservePlayer(string("Matisse Thybulle"), 24, string("SG")));
    sixers->addReservePlayer(new ReservePlayer(string("Furkan Korkmaz"), 24, string("SF")));
    sixers->addReservePlayer(new ReservePlayer(string("Tyrese Maxey"), 20, string("PG")));

    sixers->sortStartingPlayersByAge();
    sixers->sortReservePlayersByAge();

    Team* warriors = TeamFactory::createTeam("Warriors");
    warriors->addStartingPlayer(new StartingPlayer(string("Stephen Curry"), 33, string("PG")));
    warriors->addStartingPlayer(new StartingPlayer(string("Klay Thompson"), 31, string("SG")));
    warriors->addStartingPlayer(new StartingPlayer(string("Andrew Wiggins"), 26, string("SF")));
    warriors->addStartingPlayer(new StartingPlayer(string("Draymond Green"), 31, string("PF")));
    warriors->addStartingPlayer(new StartingPlayer(string("James Wiseman"), 20, string("C")));
    warriors->addReservePlayer(new ReservePlayer(string("Jordan Poole"), 22, string("SG")));
    warriors->addReservePlayer(new ReservePlayer(string("Andre Iguodala"), 37, string("SF")));
    warriors->addReservePlayer(new ReservePlayer(string("Otto Porter Jr."), 28, string("SF")));
    warriors->addReservePlayer(new ReservePlayer(string("Nemanja Bjelica"), 33, string("PF")));
    warriors->addReservePlayer(new ReservePlayer(string("Kevon Looney"), 25, string("C")));

    warriors->sortStartingPlayersByAge();
    warriors->sortReservePlayersByAge();

    //creare antrenori

    CoachPtr lakersCoach = make_shared<Coach>("Frank Vogel");
    lakers->setCoach(lakersCoach);

    CoachPtr clippersCoach = make_shared<Coach>("Tyronn Lue");
    clippers->setCoach(clippersCoach);

    CoachPtr bucksCoach = make_shared<Coach>("Mike Budenholzer");
    bucks->setCoach(bucksCoach);

    CoachPtr netsCoach = make_shared<Coach>("Steve Nash");
    nets->setCoach(netsCoach);

    CoachPtr sixersCoach = make_shared<Coach>("Doc Rivers");
    sixers->setCoach(sixersCoach);

    CoachPtr warriorsCoach = make_shared<Coach>("Steve Kerr");
    warriors->setCoach(warriorsCoach);

    // Creare turneu
    string tournamentName;
    cout << "Please provide tournament name:";
    cin >> tournamentName;
    Tournament tournament(tournamentName, 10, 15);
    tournament.addTeam(lakers);
    tournament.addTeam(clippers);
    tournament.addTeam(bucks);
    tournament.addTeam(nets);
    tournament.addTeam(sixers);
    tournament.addTeam(warriors);

    teams.push_back(lakers);
    teams.push_back(clippers);
    teams.push_back(bucks);
    teams.push_back(nets);
    teams.push_back(sixers);
    teams.push_back(warriors);




    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> score_dist(90, 120);  // Genereaza un scor intre 90-120


    // Simulari pentru meciuri
    GameStats game1(lakers, clippers);
    tournament.addGame(&game1);
    game1.setScore1(score_dist(gen));
    game1.setScore2(score_dist(gen));
    game1.updateWinLose();
    game1.updateStats();

    GameStats game2(bucks, nets);
    tournament.addGame(&game2);
    game2.setScore1(score_dist(gen));
    game2.setScore2(score_dist(gen));
    game2.updateWinLose();
    game2.updateStats();


    GameStats game3(sixers, warriors);
    tournament.addGame(&game3);
    game3.setScore1(score_dist(gen));
    game3.setScore2(score_dist(gen));
    game3.updateWinLose();
    game3.updateStats();


    GameStats game4(lakers, nets);
    tournament.addGame(&game4);
    game4.setScore1(score_dist(gen));
    game4.setScore2(score_dist(gen));
    game4.updateWinLose();
    game4.updateStats();

    GameStats game5(bucks, warriors);
    tournament.addGame(&game5);
    game5.setScore1(score_dist(gen));
    game5.setScore2(score_dist(gen));
    game5.updateWinLose();
    game5.updateStats();

    GameStats game6(clippers, sixers);
    tournament.addGame(&game6);
    game6.setScore1(score_dist(gen));
    game6.setScore2(score_dist(gen));
    game6.updateWinLose();
    game6.updateStats();

    GameStats game7(lakers, warriors);
    tournament.addGame(&game7);
    game7.setScore1(score_dist(gen));
    game7.setScore2(score_dist(gen));
    game7.updateWinLose();
    game7.updateStats();

    GameStats game8(clippers, bucks);
    tournament.addGame(&game8);
    game8.setScore1(score_dist(gen));
    game8.setScore2(score_dist(gen));
    game8.updateWinLose();
    game8.updateStats();

    GameStats game9(nets, sixers);
    tournament.addGame(&game9);
    game9.setScore1(score_dist(gen));
    game9.setScore2(score_dist(gen));
    game9.updateWinLose();
    game9.updateStats();

    tournament.afisareNumGames();

    std::unordered_map<std::string, int> teamMentionCount;  ///contor pentru folosirea numelui unei echipe
    bool isFan = false;
    bool fanClubExist = false;
    int choice;
    do {
        string echipaReclama;
        cout << "Pick an action to do(1,2,3,4):" << endl;
        cout << "1.See all teams and their win/lose;" << endl;
        cout << "2.See a specific team and it's players;" << endl;
        cout << "3.See the games that a team played" << endl;
        cout << "4. See advanced statistics for a game between two teams" << endl;
        cout << "5.See the profit of the tournament or a team" << endl;
        if (isFan) {
            cout << "6. Perform special action (available only for fans)" << endl;
            cout << "7. Exit" << endl;
        }

        else cout << "6. Exit" << endl;
        cin >> choice;
        //system("pause");
        system("cls");
        // Afisare standing-uri finale
        if (choice == 1) {
            cout << "Final Standings of " << tournamentName << " :" << endl;
            const Team** teams = tournament.getTeams();
            int numTeams = tournament.getNumTeams();
            for (int i = 0; i < numTeams; i++) {
                cout << teams[i]->getName() << ": " << teams[i]->getWins() << " wins, " << teams[i]->getLosses() << " losses" << endl;
            }
            for (int i = 0; i < numTeams; i++) {
                if (teams[i]->getWins() == 3)tournament.setWinner(teams[i]->getName());
            }
            cout << "The winner team is : " << tournament.getWinner() << endl;
        }
        // Afisare jucatori echipa selectata
        if (choice == 2) {
            string echipaCautata;
            cout << "Please provide the name of the team to see the players:" << endl;
            cin >> echipaCautata;
            echipaReclama = echipaCautata;
            teamMentionCount[echipaCautata]++;///pentru reclama
            if (echipaCautata == "Lakers") {
                displayTeamPlayers(*lakers);
            }
            else if (echipaCautata == "Clippers") {
                displayTeamPlayers(*clippers);
            }
            else if (echipaCautata == "Bucks") {
                displayTeamPlayers(*bucks);
            }
            else if (echipaCautata == "Nets") {
                displayTeamPlayers(*nets);
            }
            else if (echipaCautata == "Sixers") {
                displayTeamPlayers(*sixers);
            }
            else if (echipaCautata == "Warriors") {
                displayTeamPlayers(*warriors);
            }
            else {
                cout << "Team not found." << endl;
            }
        }
        // Afisare meciuri echipa selectata
        if (choice == 3) {
            string echipaCautata;
            cout << "Please provide the name of the team to see their matches:" << endl;
            cin >> echipaCautata;
            echipaReclama = echipaCautata;
            teamMentionCount[echipaCautata]++;///pentru reclama

            showMatches(echipaCautata, tournament);
        }


        // Afisare statistici avansate pentru un meci
        if (choice == 4) {
            // Cererea numelui celor două echipe
            string teamName1, teamName2;
            cout << "Enter the name of the first team: ";
            cin >> teamName1;
            cout << "Enter the name of the second team: ";
            cin >> teamName2;

            teamMentionCount[teamName1]++;///pentru reclama
            teamMentionCount[teamName2]++;///pentru reclama
            if (teamMentionCount[teamName1] > teamMentionCount[teamName2])echipaReclama = teamName1;
            else echipaReclama = teamName2;

            // Căutarea meciului în turneu
            const Game** games = tournament.getGames();
            int numGames = tournament.getNumGames();

            const Game** foundGame = std::find_if(games, games + numGames,
                [&](const Game* game) {
                    return game->getTeam1()->getName() == teamName1 && game->getTeam2()->getName() == teamName2;
                });

            if (foundGame != games + numGames) {
                // Am găsit meciul între echipele specificate
                // Utilizare *foundGame pentru a accesa și manipula meciul găsit
                (*foundGame)->displayStats();
            }
            else {
                // Nu s-a găsit niciun meci între echipele specificate
                throw InvalidTeamException("Invalid team name");
            }
        }

        // Calculam profitul
        if (choice == 5) {
            cout << "Write one of the following to see their profit: team name, tournament name: " << endl;
            string name;
            cin >> name;

            // Căutăm numele în lista de echipe
            std::vector<Team*>::iterator foundTeam = std::find_if(teams.begin(), teams.end(),
                [&](const Team* team) {
                    return team->getName() == name;
                });

            if (foundTeam != teams.end()) {
                // Am găsit echipa, calculăm profitul
                ProfitCalculator<Team*> profitCalculator;
                float profit = profitCalculator.calculateProfit(*foundTeam);
                cout << "The profit for team " << name << " is: " << profit << endl;
            }
            else {
                // Nu am găsit echipa, verificăm dacă este turneul
                if (tournament.getName() == name) {
                    ProfitCalculator<Tournament> profitCalculator;
                    float profit = profitCalculator.calculateProfit(tournament);
                    cout << "The profit for the tournament is: " << profit << endl;
                }
                else {
                    // Numele nu corespunde cu nicio echipă sau cu turneul
                    cout << "Name does not match any team or the tournament" << endl;
                }
            }
        }






        TeamFanClub fanClub(echipaReclama);


        if (choice == 6 && isFan) {
            fanClub.joinFanClub();
            fanClubActions(fanClub, isFan);
            fanClubExist = true;
        }

        if (!isFan && choice == 6) {

            if (fanClubExist == true)
            {
                choice = 4;
                fanClubExist = false;
                cout << "You are not a fan of any team." << endl;
            }



        }



        system("pause");
        system("cls");


        ///daca contorul pentru orice echipa ajunge la 3
        if (teamMentionCount[echipaReclama] == 3) {
            cout << "You mentioned the team " << echipaReclama << " three times. Do you want to join the fan club? (Y/N): ";

            char response;
            cin >> response;

            if (response == 'Y' || response == 'y') {
                fanClub.joinFanClub();

                isFan = true;
                fanClubActions(fanClub, isFan);
            }
            else {
                cout << "You have chosen not to join the fan club of " << echipaReclama << "." << endl;
            }

            system("pause");
            system("cls");
        }


    } while ((choice > 0 && choice < 7 && isFan == true) || (choice > 0 && choice < 6));
    return 0;
}