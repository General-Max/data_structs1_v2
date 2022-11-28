#include "Team.h"
#include "Player.h"

Team::Team(int teamId, int points) : m_teamId(teamId),m_points(points), m_playedTogether(0),
                                     m_totalPlayers(0), m_totalGoals(0), m_totalCards(0), m_goalkeepers(0) {}

int Team::getTeamId() const
{
    return this->m_teamId;
}
int Team::getPoints() const
{
    return this->m_points;
}
int Team::getPlayedTogether() const
{
    return this->m_playedTogether;
}

int Team::getTotalPlayers() const
{
    return this->m_totalPlayers;
}

int Team::getTotalGoals() const
{
    return this->m_totalGoals;
}

int Team::getTotalCards() const
{
    return this->m_totalCards;
}

void Team::increasePlayedTogether()
{
    this->m_playedTogether++;
}

void Team::setTotalPlayers(int totalPlayers)
{
    this->m_totalPlayers = totalPlayers;
}

void Team::setTotalGoals(int totalGoals)
{
    this->m_totalGoals = totalGoals;
}

void Team::setTotalCards(int totalCards)
{
    this->m_totalCards = totalCards;
}

bool Team::isEmptyTeam() const {
    return m_totalPlayers == 0;
}

void Team::insertPlayer(Player* player)
{
    if(player->getGoalKeeper()){
        this->m_goalkeepers++;
    }
    m_teamPlayersByID.insert(player);
    m_teamPlayersByScore.insert(player);
    m_totalCards+=player->getCards();
    m_totalGoals+=player->getGoals();
    m_totalPlayers++;
    //needs to be finishid!!!!
}

void Team::updatePoints(int points) {
    this->m_points += points;
}

int Team::getScore() const
{
    return this->m_points+this->m_totalCards-m_totalCards;
}

void Team::removePLayer(Player *player) {
    if(player->getGoalKeeper()){
        this->m_goalkeepers--;
    }
    m_teamPlayersByID.remove(player);
    m_teamPlayersByScore.remove(player);
    m_totalCards-=player->getCards();
    m_totalGoals-=player->getGoals();
    m_totalPlayers--;
    
}

int Team::getGoalkeepers() const {
    return m_goalkeepers;
}

AVLTree<Player*, SortByScore> Team::getScoreTree() const
{
    return this->m_teamPlayersByScore;
}

AVLTree<Player*, SortById> Team::getIdTree() const
{
    return this->m_teamPlayersByID;
}
