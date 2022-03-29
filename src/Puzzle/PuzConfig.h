///////////////////////////////////////////////////////////////

//
// PuzConfig.h
//
//   Puzzle Configuration Class
//
// by Peng SONG ( peng_song@sutd.edu.sg )
//
// 22/Aug/2021
//

///////////////////////////////////////////////////////////////

#ifndef _PUZ_CONFIG_H
#define _PUZ_CONFIG_H

#include "Utility/HelpPuz.h"


#define CONFIG_OUT_LIST              -1

#define PUZ_CONFIG_UNKNOWN           -1
#define PUZ_CONFIG_ROOT               0
#define PUZ_CONFIG_TARGET_CANDI       1
#define PUZ_CONFIG_TARGET             2
#define PUZ_CONFIG_SHORTEST_PATH      3
#define PUZ_CONFIG_PIECE_ONLY         4
#define PUZ_CONFIG_PIECE_REMOVE       5
#define PUZ_CONFIG_GROUP_REMOVE       6
#define PUZ_CONFIG_END_NODE           7


class PuzConfig
{
public:
    int puzConfigID;                    // PuzConfig ID in the graph

	vector<int> pieceIDList;            // Each pieceID in the config
	vector<Vector3i> piecePosList;      // Offset position of each piece

	vector<PuzConfig*> nextPuzConfigs;  // Next possible puzzle config

	int distToRoot;                     // Distance to the root node
	int configType;                     // Type of the node (root, target, target candidate, shortest path)
	bool isTraced;                      // For tracing nodes in the PuzConfig graph
	bool isInKernelGraph = false;

    vector<int> remvPieceIDs;           // Pieces that can be removed in the config (only assigned values when configType = PUZ_CONFIG_TARGET)
    vector<int> remvAxisIDs;            // Pieces' possible removable axis          (only assigned values when configType = PUZ_CONFIG_TARGET)

    vector<int> moveAxisIDs;            // The motion space of the SeedPath in this PuzConfig

public:
	PuzConfig();
	~PuzConfig();
	//PuzConfig & operator=(const PuzConfig & puzConfig);
	bool operator==(const PuzConfig & puzConfig);
	void InitiConfig(vector<int> puzPieceIDs);
    void PrintPuzConfig(bool isShowNextConfig);

    /// Create Next PuzConfig
    void CreateNextConfig(vector<int> pieceIDIndices, int moveAxisID, int moveStep, vector<PuzConfig*> &existingConfigs);
    int FindPuzConfigInList(PuzConfig *tagtPuzConfig, vector<PuzConfig*> puzConfigList);

   /// Create Next PuzConfig (Remove Pieces)
	void RemovePieceIDs(vector<int> removablePieceIDs, PuzConfig *newPuzConfig);
	Vector3i GetPiecePos(int pieceID);
};

#endif
