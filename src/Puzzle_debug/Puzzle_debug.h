//
// Created by Linsanity on 24/7/21.
//

#ifndef HIGHLEVELPUZZLE_LIBIGL_PUZZLE_DEBUG_H
#define HIGHLEVELPUZZLE_LIBIGL_PUZZLE_DEBUG_H

#include "Piece_debug.h"

class Puzzle_debug
{
public:
    Puzzle origPuzzle;

    vector<Piece_debug> piece_debug_List;

public:
    void ClearPuzzle_debug();

    ////////////////////////////////////////////////////

    /// TODO: Finish these two functions
    void SavePuzzleDebugInfo();

    void ReadPuzzleDebugInfo();

    ////////////////////////////////////////////////////

};

#endif //HIGHLEVELPUZZLE_LIBIGL_PUZZLE_DEBUG_H
