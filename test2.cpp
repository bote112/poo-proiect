#include <iostream>
#include <cstring>
#include <cstdlib> // pentru system("clear")
#include <random>
using namespace std;



// Clasa inlocuitoare pentru std::string
class MyString {
public:
    MyString() : m_data(nullptr), m_size(0) {}

    MyString(const char* str) : m_data(nullptr), m_size(0) {
        if (str) {
            m_size = strlen(str);
            m_data = new char[m_size + 1];
            strcpy_s(m_data, m_size + 1, str);
        }
    }

    MyString(const MyString& other) : m_data(nullptr), m_size(0) {
        if (other.m_data) {
            m_size = other.m_size;
            m_data = new char[m_size + 1];
            strcpy_s(m_data, m_size + 1, other.m_data);
        }
    }

    MyString(MyString&& other) noexcept : m_data(other.m_data), m_size(other.m_size) {
        other.m_data = nullptr;
        other.m_size = 0;
    }
    
    ~MyString() {
        delete[] m_data;
    }
    
    MyString& operator=(const char* str) {
        if (m_data) {
            delete[] m_data;
            m_data = nullptr;
            m_size = 0;
        }
        if (str) {
            m_size = strlen(str);
            m_data = new char[m_size + 1];
            strcpy_s(m_data, m_size + 1, str);
        }
        return *this;
    }

    MyString& operator=(const MyString& other) {
        if (this != &other) {
            if (m_data) {
                delete[] m_data;
                m_data = nullptr;
                m_size = 0;
            }
            if (other.m_data) {
                m_size = other.m_size;
                m_data = new char[m_size + 1];
                strcpy_s(m_data, m_size + 1, other.m_data);
            }
        }
        return *this;
    }

    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            if (m_data) {
                delete[] m_data;
                m_data = nullptr;
                m_size = 0;
            }
            m_data = other.m_data;
            m_size = other.m_size;
            other.m_data = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    char& operator[](int index) {
        return m_data[index];
    }

    const char& operator[](int index) const {
        return m_data[index];
    }

    bool operator==(const MyString& other) const {
        return (m_size == other.m_size && strcmp(m_data, other.m_data) == 0);
    }

    bool operator!=(const MyString& other) const {
        return !(*this == other);
    }

    size_t size() const {
        return m_size;
    }

    const char* c_str() const {
        return m_data;
    }

    void clear() {
        if (m_data) {
            delete[] m_data;
            m_data = nullptr;
            m_size = 0;
        }
    }

private:
    char* m_data;
    size_t m_size;
};

std::ostream& operator<<(std::ostream& os, const MyString& str) {
    os << str.c_str();
    return os;
}

std::istream& operator>>(std::istream& is, MyString& str) {
    char buffer[1024];
    is >> buffer;
    str = buffer;
    return is;
}




// Clasa pentru jucătorul de basket
class Player {
private:
    MyString name;
    int age;
    MyString position;
public:
    Player(MyString name, int age, MyString position) {
        this->name = name;
        this->age = age;
        this->position = position;
    }
    MyString getName() const { return name; }
    int getAge() const { return age; }
    MyString getPosition() const { return position; }
};

// Clasa pentru echipa de basket
class Team {
private:
    MyString name;
    Player* players[10]; // maxim 10 jucatori la o echipa
    int numPlayers;
    int maxPlayers;
    int wins;
    int losses;
public:
    Team(MyString name) {
        this->name = name;
        this->wins = 0;
        this->losses = 0;
        this->numPlayers = 0;
        this->maxPlayers = 5;
        memset(players, 0, sizeof(players));
    }
   
    MyString getName() const { return name; }
    const Player** getPlayers() const { return (const Player**)players; }
    int getNumPlayers() const { return numPlayers; }
    int getWins() const { return wins; }
    int getLosses() const { return losses; }
    void addWin() { wins++; }
    void addLoss() { losses++; }
    void addPlayer(Player* player) {
        if (numPlayers < maxPlayers) {
            players[numPlayers++] = player;
        }
    }
};

// Clasa pentru meciul de basket
class Game {
private:
    Team* team1;
    Team* team2;
    int score1;
    int score2;
public:
    Game(Team* team1, Team* team2) {
        this->team1 = team1;
        this->team2 = team2;
        score1 = 0;
        score2 = 0;
    }
    ~Game() {
        // Nu este memorie alocata 
    }
    Team* getTeam1() const { return team1; }
    Team* getTeam2() const { return team2; }
    int getScore1() const { return score1; }
    int getScore2() const { return score2; }
    void setScore1(int score) { score1 = score; }
    void setScore2(int score) { score2 = score; }
    // Metoda pentru determinarea castigatorului si update-ul la win/lose
    void updateStats() {
        if (score1 > score2) {
            team1->addWin();
            team2->addLoss();
        }
        else if (score2 > score1) {
            team2->addWin();
            team1->addLoss();
        }
    }
};


// Clasa pentru turneul de basket
class Tournament {
private:
    MyString name;
    Game** games;
    int numGames;
    int maxGames;
    Team** teams;
    int numTeams;
    int maxTeams;
    MyString winner;
public:
    Tournament(MyString name, int maxTeams, int maxGames) {
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

    const MyString& getName() const {
        return name;
    }

    int getNumTeams() const {
        return numTeams;
    }

    int getNumGames() const {
        return numGames;
    }

    void setWinner(MyString winner) { 
        this->winner = winner; 
        system("pause");
        system("cls");
        cout << "The games are being procesed..." << endl;
    }

    MyString getWinner() {
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
        cout << "The number of games that are being played is: " << numGames << endl<<endl;
        system("pause");
    }

    const Team** getTeams() const {
        return (const Team**)teams;
    }

    const Game** getGames() const {
        return (const Game**)games;
    }

    void play() {
        for (int i = 0; i < numGames; i++) {
            games[i]->updateStats();
        }
    }
};
// Afiseaza jucatorii unei echipe in functie de inputul din consola
void displayTeamPlayers(const Tournament& tournament, const MyString& teamName) {
    const Team** teams = tournament.getTeams();
    int numTeams = tournament.getNumTeams();

    for (int i = 0; i < numTeams; i++) {
        if (teams[i]->getName() == teamName) {
            const Player** players = teams[i]->getPlayers();
            int numPlayers = teams[i]->getNumPlayers();

            cout << "Players for team " << teamName << ":" << endl;
            for (int j = 0; j < numPlayers; j++) {
                cout << players[j]->getName() << " - " << players[j]->getAge() << " - " << players[j]->getPosition() <<endl;
            }
            return;
        }
    }
    cout << "Team " << teamName << " not found." << endl;
}
// Afiseaza meciuri jucate de o echipa
void showMatches(const MyString& teamName, const Tournament& tournament) {
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
        cout << "No matches found for team " << teamName << endl;
    }
}



int main() {

    MyString lakersName("Lakers");
    Team lakers(lakersName);
    lakers.addPlayer(new Player(MyString("LeBron James"), 37, MyString("SF")));
    lakers.addPlayer(new Player(MyString("Anthony Davis"), 28, MyString("PF")));
    lakers.addPlayer(new Player(MyString("Russell Westbrook"), 33, MyString("PG")));
    lakers.addPlayer(new Player(MyString("Carmelo Anthony"), 37, MyString("SF")));
    lakers.addPlayer(new Player(MyString("Dwight Howard"), 36, MyString("C")));

    MyString clippersName("Clippers");
    Team clippers(clippersName);
    clippers.addPlayer(new Player(MyString("Kawhi Leonard"), 30, MyString("SF")));
    clippers.addPlayer(new Player(MyString("Paul George"), 31, MyString("SG")));
    clippers.addPlayer(new Player(MyString("Serge Ibaka"), 32, MyString("PF")));
    clippers.addPlayer(new Player(MyString("Reggie Jackson"), 31, MyString("PG")));
    clippers.addPlayer(new Player(MyString("Marcus Morris"), 32, MyString("PF")));

    MyString bucksName("Bucks");
    Team bucks(bucksName);
    bucks.addPlayer(new Player(MyString("Giannis Antetokounmpo"), 27, MyString("PF")));
    bucks.addPlayer(new Player(MyString("Khris Middleton"), 30, MyString("SF")));
    bucks.addPlayer(new Player(MyString("Jrue Holiday"), 31, MyString("PG")));
    bucks.addPlayer(new Player(MyString("Brook Lopez"), 33, MyString("C")));
    bucks.addPlayer(new Player(MyString("Pat Connaughton"), 28, MyString("SG")));

    MyString netsName("Nets");
    Team nets(netsName);
    nets.addPlayer(new Player(MyString("Kevin Durant"), 33, MyString("SF")));
    nets.addPlayer(new Player(MyString("James Harden"), 32, MyString("SG")));
    nets.addPlayer(new Player(MyString("Kyrie Irving"), 29, MyString("PG")));
    nets.addPlayer(new Player(MyString("Blake Griffin"), 32, MyString("PF")));
    nets.addPlayer(new Player(MyString("LaMarcus Aldridge"), 36, MyString("C")));

    MyString sixersName("Sixers");
    Team sixers(sixersName);
    sixers.addPlayer(new Player(MyString("Joel Embiid"), 27, MyString("C")));
    sixers.addPlayer(new Player(MyString("Ben Simmons"), 24, MyString("PG")));
    sixers.addPlayer(new Player(MyString("Tobias Harris"), 28, MyString("SF")));
    sixers.addPlayer(new Player(MyString("Seth Curry"), 31, MyString("SG")));
    sixers.addPlayer(new Player(MyString("Danny Green"), 34, MyString("SF")));

    MyString warriorsName("Warriors");
    Team warriors(warriorsName);
    warriors.addPlayer(new Player(MyString("Stephen Curry"), 33, MyString("PG")));
    warriors.addPlayer(new Player(MyString("Klay Thompson"), 31, MyString("SG")));
    warriors.addPlayer(new Player(MyString("Draymond Green"), 31, MyString("PF")));
    warriors.addPlayer(new Player(MyString("Andrew Wiggins"), 26, MyString("SF")));
    warriors.addPlayer(new Player(MyString("James Wiseman"), 20, MyString("C")));

    // Creare turneu
    MyString tournamentName;
    cout << "Please provide tournament name:";
    cin >> tournamentName;
    Tournament tournament(tournamentName, 10, 15);
    tournament.addTeam(&lakers);
    tournament.addTeam(&clippers);
    tournament.addTeam(&bucks);
    tournament.addTeam(&nets);
    tournament.addTeam(&sixers);
    tournament.addTeam(&warriors);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> score_dist(90, 120);  // Genereaza un scor intre 90-120


    // Simulari pentru meciuri
    Game game1(&lakers, &clippers);
    tournament.addGame(&game1);
    game1.setScore1(score_dist(gen));
    game1.setScore2(score_dist(gen));
    game1.updateStats();

    Game game2(&bucks, &nets);
    tournament.addGame(&game2);
    game2.setScore1(score_dist(gen));
    game2.setScore2(score_dist(gen));
    game2.updateStats();

    Game game3(&sixers, &warriors);
    tournament.addGame(&game3);
    game3.setScore1(score_dist(gen));
    game3.setScore2(score_dist(gen));
    game3.updateStats();

    Game game4(&lakers, &nets);
    tournament.addGame(&game4);
    game4.setScore1(score_dist(gen));
    game4.setScore2(score_dist(gen));
    game4.updateStats();

    Game game5(&bucks, &warriors);
    tournament.addGame(&game5);
    game5.setScore1(score_dist(gen));
    game5.setScore2(score_dist(gen));
    game5.updateStats();

    Game game6(&clippers, &sixers);
    tournament.addGame(&game6);
    game6.setScore1(score_dist(gen));
    game6.setScore2(score_dist(gen));
    game6.updateStats();

    Game game7(&lakers, &warriors);
    tournament.addGame(&game7);
    game7.setScore1(score_dist(gen));
    game7.setScore2(score_dist(gen));
    game7.updateStats();

    Game game8(&clippers, &bucks);
    tournament.addGame(&game8);
    game8.setScore1(score_dist(gen));
    game8.setScore2(score_dist(gen));
    game8.updateStats();

    Game game9(&nets, &sixers);
    tournament.addGame(&game9);
    game9.setScore1(score_dist(gen));
    game9.setScore2(score_dist(gen));
    game9.updateStats();

    tournament.afisareNumGames();

    int choice;
    do {
        cout << "Pick an action to do(1,2,3,4):" << endl << "1.See all teams and their win/lose;" << endl << "2.See a specific team and it's players;" << endl << "3.See the games that a team played" << endl << "4.Exit" << endl;
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
            cout <<"The winner team is : "<<tournament.getWinner()<<endl;
        }
        // Afisare jucatori echipa selectata
        if (choice == 2) {
            MyString echipaCautata;
            cout << "Please provide the name of the team to see the players:" << endl;
            cin >> echipaCautata;
            displayTeamPlayers(tournament, echipaCautata);
        }
        // Afisare meciuri echipa selectata
        if (choice == 3) {
            MyString echipaCautata;
            cout << "Please provide the name of the team to see their matches:" << endl;
            cin >> echipaCautata;
            showMatches(echipaCautata, tournament);
        }
        system("pause");
        system("cls");
    } while (choice == 1 || choice == 2 || choice == 3);
    return 0;
}
