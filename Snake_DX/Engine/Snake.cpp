#include "Snake.h"
#include<assert.h>


Snake::Snake(const Location& loc)
{
	//create 4 different colors
	const int nBodyColors = 4;
	constexpr Color bodyColors[nBodyColors]=
	{
		{10,100,32},{10,130,48},{18,160,48},{10,130,48}
	};
	//assign colors to segments
	for (int i = 0; i < nSegmentsMax; i++)
	{
		segments[i].InitBody(bodyColors[i%nBodyColors]);
	}
	//set head position
	segments[0].InitHead(loc);
}


void Snake::MoveBy(const Location & delta_loc)
{
	//move segment like previous one
	for (int i = nSegments - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i-1]);
	}
	segments[0].MoveBy(delta_loc);
}

Location Snake::GetNextHeadLocation(const Location & delta_location) const
{
	Location l = segments[0].getLocation();
   l.Add(delta_location);
   return l;
}

//add new segment
void Snake::Grow()
{
	if (nSegments < nSegmentsMax) 
	{
	    nSegments++;
	}
}

void Snake::Draw(Board & brd) const
{
	//draw all segments of snake
	for (int i = 0; i < nSegments; i++)
	{
		segments[i].DrawSegment(brd);
	}
}

Snake::~Snake()
{
}

//suicide check
bool Snake::isInTile(const Location& Tileloc) const
{
	for (int i = 0; i < nSegments-1; i++)
	{
		if (segments[i].getLocation()==Tileloc)
		{
			return true;
		}
	}
	return false;
}



void Snake::Segment::InitHead(const Location & in_loc)
{
	segmentloc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(Color _c)
{
	c = _c;
}

void Snake::Segment::MoveBy(const Location & delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y)==1);
	segmentloc.Add(delta_loc);
}

void Snake::Segment::Follow(const Segment & nextSegment)
{
	
	segmentloc = nextSegment.segmentloc;
}

void Snake::Segment::DrawSegment(Board & brd) const
{
	brd.DrawCell(segmentloc, c);
	
}

const Location& Snake::Segment::getLocation() const
{
	return segmentloc;
}
