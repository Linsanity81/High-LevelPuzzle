//
// Created by Linsanity on 24/7/21.
//

#ifndef HIGHLEVELPUZZLE_LIBIGL_PIECE_DEBUG_H
#define HIGHLEVELPUZZLE_LIBIGL_PIECE_DEBUG_H

#include "Puzzle/PieceCreator.h"
#include "Puzzle/PuzConfig.h"
#include "Puzzle/Puzzle.h"

class Piece_debug
{
public:

    PuzConfig furthestPuzConfig;

    int pieceAxisID;

    // Note: These variables are for debug

    vector<Vector3i> _ContaVoxels;      // Draw the voxels for debug

    vector<Vector3i> _SeedVoxels;
    vector<Vector3i> _SeedKeptVoxels;
    vector<Vector3i> _SeedPathVoxels;

    vector<Vector3i> _BlockVoxel;
    vector<Vector3i> _BlockKeptVoxels;
    vector<Vector3i> _BlockPathVoxels;

    vector<Vector3i> _ExtdVoxels;
    vector<Vector3i> _ExtdExpVoxelCandis;

};

#endif //HIGHLEVELPUZZLE_LIBIGL_PIECE_DEBUG_H
