#include "worldcup23a1.h"
#include "Team.h"
#include "Player.h"

world_cup_t::world_cup_t() : m_numPlayers(0) {}

world_cup_t::~world_cup_t()
{
    // TODO: check if needed: delete m_topScorer
    // TODO:: check if all the rest deleted automatically because destroying this call each one destructor
}


StatusType world_cup_t::add_team(int teamId, int points)
{
    // TODO: Your code goes here
    if(teamId<=0 || points<0){
        return StatusType::INVALID_INPUT;
    }

    if(m_teams.find(teamId)){
        return StatusType::FAILURE;
    }
    Team* newTeam = new Team(teamId, points);
    try{
        m_teams.insert(newTeam);
    }
    catch(std::bad_alloc&){
        delete newTeam;
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId<=0){
        return StatusType::INVALID_INPUT;
    }
    if((!m_teams.find(teamId)) || !(*m_teams.find(teamId)->getData())->isEmptyTeam()){
        return StatusType::FAILURE;
    }
    try{
        m_teams.remove(teamId);
        if((m_validTeams.find(teamId)) && (*m_validTeams.find(teamId)->getData())->isEmptyTeam()){
            m_validTeams.remove(teamId);
        }
    }
    catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    // TODO: Your code goes here
    if(playerId<=0 || teamId<=0 || gamesPlayed<0 || goals<0 ||cards<0 || (gamesPlayed=0 && (goals>0 || cards>0))){
        return StatusType::INVALID_INPUT;
    }

    if(m_teams.find(teamId) == nullptr || m_playersById.find(playerId) != nullptr){
        return StatusType::FAILURE;
    }
    try{
        Team* currentTeam = *m_teams.find(teamId)->getData();
        auto* newPlayer = new Player(playerId, teamId, gamesPlayed-currentTeam->getPlayedTogether(),
                                     goals, cards, goalKeeper);
        //currentTeam->setPlayedTogether(0);
        newPlayer->setTeamPtr(currentTeam);
        m_playersById.insert(newPlayer);
        m_playersByScore.insert(newPlayer);
        m_numPlayers++;

        currentTeam->insertPlayer(newPlayer);
        addIfValidTeam(currentTeam);
        insertPlayerToList(m_playersByScore.find(newPlayer));
//        std::cout << "players by id: " <<std::endl;
//        m_playersByScore.printD(m_playersById.getRoot(), 10);
//        std::cout << "players by id: " <<std::endl;
//        m_playersByScore.printD(m_playersByScore.getRoot(), 10);
   //     m_playersListByScore.printList();
    }
    catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
    // TODO: Your code goes here
    if(playerId<=0){
        return StatusType::INVALID_INPUT;
    }
    if(m_playersById.find(playerId) == nullptr){
        return StatusType::FAILURE;
    }
    try{
        Player* playerToRemove = *m_playersById.find(playerId)->getData();
        Team* playerTeam = playerToRemove->getTeamPtr();
        m_playersListByScore.removeNode(playerToRemove->getDequePtr());
        m_playersById.remove(playerId);
        m_playersByScore.remove(playerToRemove);
        playerTeam->removePLayer(playerToRemove);
        removeIfNodValidTeam(playerTeam);
//        std::cout << "AFTER REMOVE players by id: " <<std::endl;
//        m_playersByScore.printD(m_playersById.getRoot(), 10);
//        std::cout << "AFTER REMOVE players by score: " <<std::endl;
       // m_playersByScore.printD(m_playersByScore.getRoot(), 10);
 //       m_playersListByScore.printList();
        m_numPlayers--;
    }
    catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                            int scoredGoals, int cardsReceived)
{
    // TODO: Your code goes here
    if(playerId<=0 || gamesPlayed<0 || scoredGoals<0 || cardsReceived<0){
        return StatusType::INVALID_INPUT;
    }
    if(m_playersById.find(playerId) == nullptr){
        return StatusType::FAILURE;
    }
    try{
        Player* currentPlayer = *m_playersById.find(playerId)->getData();
        Team* currentTeam = currentPlayer->getTeamPtr();
        m_playersByScore.remove(currentPlayer);
        m_playersListByScore.removeNode(currentPlayer->getDequePtr());
        currentTeam->removePLayer(currentPlayer);

        currentPlayer->updateGamesPlayed(gamesPlayed);
        currentPlayer->updateGoals(scoredGoals);
        currentPlayer->updateCards(cardsReceived);

    //    m_playersListByScore.printList();
        m_playersByScore.insert(currentPlayer);
        currentTeam->insertPlayer(currentPlayer);
        insertPlayerToList(m_playersByScore.find(currentPlayer));
    }
    catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
    // TODO: Your code goes here
    if(teamId1<=0 || teamId2<=0 || teamId1==teamId2){
        return StatusType::INVALID_INPUT;
    }
    BinNode<Team*>* team1 = m_validTeams.find(teamId1);
    BinNode<Team*>* team2 = m_validTeams.find(teamId2);
    
    if(team1==nullptr || team2==nullptr){
        return StatusType::FAILURE;
    }
    try{
        if((*team1->getData())->getScore()>(*team2->getData())->getScore()){
            (*team1->getData())->updatePoints(WIN);
        }
        else if((*team1->getData())->getScore()<(*team2->getData())->getScore()){
            (*team2->getData())->updatePoints(WIN);
        }
        else{
            (*team1->getData())->updatePoints(DRAW);
            (*team2->getData())->updatePoints(DRAW);
        }
        (*team1->getData())->increasePlayedTogether();
        (*team2->getData())->increasePlayedTogether();
    }
    catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
    // TODO: Your code goes here
    if(playerId<=0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    BinNode<Player*>* player = m_playersById.find(playerId);
    if(player==nullptr){
        return StatusType::FAILURE;
    }

    int played=0;
    try
    {
        played+=(*player->getData())->getGamesPlayed();
        int playedWithTeam=0;
        playedWithTeam=(*player->getData())->getTeamPtr()->getPlayedTogether();
        played+=playedWithTeam;
    }
    catch(std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    

    return played;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    // TODO: Your code goes here
    if(teamId<=0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    BinNode<Team*>* team = m_teams.find(teamId);
    if(team==nullptr){
        return StatusType::FAILURE;
    }

    int points=0;
    try
    {
        points=(*team->getData())->getPoints();
    }
    catch(std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    

    return points;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
    // TODO: Your code goes here
    if(newTeamId<=0 || teamId1<=0 || teamId2<=0 || teamId1==teamId2){
        return StatusType::INVALID_INPUT;
    }

    BinNode<Team*>* team1 = m_teams.find(teamId1);
    BinNode<Team*>* team2 = m_teams.find(teamId2);
    BinNode<Team*>* newTeam = m_teams.find(newTeamId);
    
    if(team1==nullptr || team2==nullptr || ((newTeam!= nullptr && newTeamId!=teamId1) && (newTeam!= nullptr && newTeamId!=teamId2))){
        return StatusType::FAILURE;
    }
    try{
        if(teamId1==newTeamId){
            merge(*team1->getData(), *team2->getData());
        }
        else if(teamId2==newTeamId){
            merge(*team2->getData(), *team1->getData());
        }
        else{
            ;
            //unite(*team1->getData(), *team1->getData(), newTeamId);
        }
    
    }
    catch(std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    

    return StatusType::SUCCESS;
}


output_t<int> world_cup_t::get_top_scorer(int teamId)
{
    if(teamId==0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    if(teamId>0){
        // check if team
        if(m_numPlayers==0){
            return output_t<int>(StatusType::FAILURE);
        }
        //this is the top scorer player
        Player * p = *m_playersByScore.getMaxValueInTree();
        //return output_t<int>();
    }

    //search for the team if couldnt find throw error
    return output_t<int>(6);//should be the id of the top scorer in the team
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
    if(teamId==0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    if(teamId<0){
        return output_t<int>(m_numPlayers);
    }

    //search for the team if couldnt find throw error
    return output_t<int>(6);//should by the number of players in the team
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
    // TODO: Your code goes here
    if(output==nullptr || teamId==0){
        return StatusType::INVALID_INPUT;
    }

    output[0] = 4001;
    output[1] = 4002;
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
    // TODO: Your code goes here
    if(teamId<=0 || playerId<=0){
        return StatusType::INVALID_INPUT;
    }
    return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
    // TODO: Your code goes here
    if(minTeamId<0 || maxTeamId<0 || maxTeamId<minTeamId){
        return StatusType::INVALID_INPUT;
    }

    return 2;
}

bool world_cup_t::isValidTeam(Team *team) {
    return (team->getTotalPlayers()>=PLAYERS_NUM_IN_VALID_TEAM && team->getGoalkeepers()>0);
}

void world_cup_t::addIfValidTeam(Team *team) {
    // if the team keeps the valid teams condition and is not in the tree
    if (isValidTeam(team) && m_validTeams.find(team->getTeamId()) == nullptr){
        m_validTeams.insert(team);
    }
}

void world_cup_t::removeIfNodValidTeam(Team *team) {
// if the team doesn't keep the valid teams condition and is in the tree
    if (!isValidTeam(team) && m_validTeams.find(team->getTeamId()) != nullptr){
        m_validTeams.remove(team);
    }
}

void world_cup_t::insertPlayerToList(BinNode<Player *> *newNode) {
    auto* newListNode = new ListNode<Player*>(*newNode->getData());
    (*newNode->getData())->setDequePtr(newListNode);
    // in case it is the first element in the list
    if (m_numPlayers == SINGLE_PLAYER){
        m_playersListByScore.setHead(newListNode);
        return;
    }
    if(newNode->getFather() != nullptr){
        if(SortByScore::lessThan(*(newNode->getFather())->getData(), *newNode->getData())){
            m_playersListByScore.insertAfter(newListNode, (*(newNode->getFather())->getData())->getDequePtr());
        }
        else{
            m_playersListByScore.insertBefore(newListNode, (*(newNode->getFather())->getData())->getDequePtr());
        }
    }
    else if(newNode->getRight()){
        m_playersListByScore.insertBefore(newListNode, (*newNode->getRight()->getData())->getDequePtr());
    }
    else{
        m_playersListByScore.insertAfter(newListNode, (*newNode->getRight()->getData())->getDequePtr());
    }
}


/*
void world_cup_t::merge(Team* target, Team* merged)
{
    while(!merged->isEmptyTeam()){

        target->insertPlayer(merged->)
    }
}
*/


