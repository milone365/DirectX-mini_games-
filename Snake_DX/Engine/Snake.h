#pragma once
#include"Board.h"

class Snake
{
private:
	class Segment 
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody(Color _c);
		void MoveBy(const Location& delta_loc);
		void Follow(const Segment& nextSegment);
		void DrawSegment(Board& brd)const;
		const Location& getLocation()const;
	private:
		Location segmentloc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	Location GetNextHeadLocation(const Location& delta_location)const;
	//add segment
	void Grow();
	void Draw(Board& brd)const;
	~Snake();
	bool isInTile(const Location& Titleloc)const;
	
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};

