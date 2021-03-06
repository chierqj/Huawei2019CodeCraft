#include "cross.h"
#include "assert.h"
#include "road.h"

Cross::Cross()
{
    ASSERT(false);
}

Cross::Cross(const int& origin, const int& id, const int& northRoadId, const int& eastRoadId, const int& southRoadId, const int& westRoadId)
    : m_originId(origin), m_id(id), m_northRoadId(northRoadId), m_eastRoadId(eastRoadId), m_southRoadId(southRoadId), m_westRoadId(westRoadId)
    , m_north(0), m_east(0), m_south(0), m_west(0)
{
    if (m_northRoadId >= 0) m_directions[m_northRoadId] = NORTH;
    if (m_eastRoadId >= 0) m_directions[m_eastRoadId] = EAST;
    if (m_southRoadId >= 0) m_directions[m_southRoadId] = SOUTH;
    if (m_westRoadId >= 0) m_directions[m_westRoadId] = WEST;
}

Cross::~Cross()
{ }

const Cross::DirectionType& Cross::GetDirection(const int& id) const
{
    auto find = m_directions.find(id);
    ASSERT(find != m_directions.end());
    return find->second;
}

Cross::TurnType Cross::GetTurnDirection(const int& from, const int& to) const
{
    switch ((int)GetDirection(to) - (int)GetDirection(from))
    {
    case 1:
    case -3:
        return Cross::LEFT;
    case -1:
    case 3:
        return Cross::RIGHT;
    case 2:
    case -2:
        return Cross::DIRECT;
    default:
        break;
    }
    ASSERT_MSG(false, "from " << from << "(" << GetDirection(from) << ") to " << to << "(" << GetDirection(to) << ")");
    return Cross::DIRECT;
}

Cross::DirectionType Cross::GetTurnDestinationDirection(const int& from, const Cross::TurnType& turn) const
{
    int dir = (int)GetDirection(from);
    switch (turn)
    {
    case LEFT: dir += 1; break;
    case DIRECT: dir += 2; break;
    case RIGHT: dir -=1; break;
    default:
        ASSERT(false);
    }
    if (dir < 0)
        dir += DirectionType_Size;
    if (dir >= DirectionType_Size)
        dir %= DirectionType_Size;
    return (DirectionType)dir;
}

Road* Cross::GetTurnDestination(const int& from, const Cross::TurnType& turn) const
{
    return GetRoad(GetTurnDestinationDirection(from, turn));
}

int Cross::GetTurnDestinationId(const int& from, const Cross::TurnType& turn) const
{
    return GetRoadId(GetTurnDestinationDirection(from, turn));
}

void Cross::SetNorthRoadId(const int& id)
{
    m_northRoadId = id;
    m_directions[id] = NORTH;
}

void Cross::SetEasthRoadId(const int& id)
{
    m_eastRoadId = id;
    m_directions[id] = EAST;
}

void Cross::SetSouthRoadId(const int& id)
{
    m_southRoadId = id;
    m_directions[id] = SOUTH;
}

void Cross::SetWestRoadId(const int& id)
{
    m_westRoadId = id;
    m_directions[id] = WEST;
}

void Cross::SetNorthRoad(Road* road)
{
    ASSERT(road->GetId() == m_northRoadId);
    m_north = road;
}

void Cross::SetEasthRoad(Road* road)
{
    ASSERT(road->GetId() == m_eastRoadId);
    m_east = road;
}

void Cross::SetSouthRoad(Road* road)
{
    ASSERT(road->GetId() == m_southRoadId);
    m_south = road;
}

void Cross::SetWestRoad(Road* road)
{
    ASSERT(road->GetId() == m_westRoadId);
    m_west = road;
}
