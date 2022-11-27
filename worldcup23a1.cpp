#include "worldcup23a1.h"
#include "Team.h"
#include "Player.h"

world_cup_t::world_cup_t() : m_numPlayers(0)
{
    //and add the rest
    //TODO: יש טעם להוסיף את האחרים או שזה כבר אותחל?
}

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
        currentTeam->setPlayedTogether(0);
        newPlayer->setTeamPtr(currentTeam);
        m_playersById.insert(newPlayer);
        m_playersByScore.insert(newPlayer);
        m_numPlayers++;

        currentTeam->insertPlayer(newPlayer);
        addIfValidTeam(currentTeam);
        insert(m_playersByScore.find(newPlayer));
//        std::cout << "players by id: " <<std::endl;
//        m_playersByScore.printD(m_playersById.getRoot(), 10);
//        std::cout << "players by id: " <<std::endl;
//        m_playersByScore.printD(m_playersByScore.getRoot(), 10);
        m_playersListByScore.printList();
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
        m_playersById.remove(playerId);
        m_playersListByScore.deleteNode(playerToRemove->getDequePtr());
        m_playersByScore.remove(playerToRemove);
        playerTeam->removePLayer(playerToRemove);
//        std::cout << "AFTER REMOVE players by id: " <<std::endl;
//        m_playersByScore.printD(m_playersById.getRoot(), 10);
//        std::cout << "AFTER REMOVE players by score: " <<std::endl;
       // m_playersByScore.printD(m_playersByScore.getRoot(), 10);
        m_playersListByScore.printList();
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

    return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
    // TODO: Your code goes here
    if(teamId1<=0 || teamId2<=0 || teamId1==teamId2){
        return StatusType::INVALID_INPUT;
    }

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
    // TODO: Your code goes here
    if(playerId<=0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    return 22;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    // TODO: Your code goes here
    if(teamId<=0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    return 30003;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
    // TODO: Your code goes here
    if(newTeamId<=0 || teamId1<=0 || teamId2<=0 || teamId1==teamId2){
        return StatusType::INVALID_INPUT;
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
    return (team->getTotalPlayers()>PLAYERS_NUM_IN_VALID_TEAM);
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

void world_cup_t::insert(BinNode<Player *> *newNode) {
    auto* newListNode = new ListNode<Player*>(*newNode->getData());
    (*newNode->getData())->setDequePtr(newListNode);
    // in case it is the first element in the list
    if (m_numPlayers == 1){
        m_playersListByScore.setHead(newListNode);
        return;
    }
    //wont work because it will create a new FatherListNodeEveryTime
    //auto* fatherListNode = new ListNode<Player*>(*newNode->getFather()->getData());
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

