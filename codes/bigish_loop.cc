TiledJet * jetA = briefjets, * jetB; //jetA and jetB are pointers to a jet-like variable.


// set up the initial nearest neighbour information
vector<Tile>::const_iterator tile;
for (tile = _tiles.begin(); tile != _tiles.end(); tile++) {//loop through all tiles
    // first do it on this tile
    for (jetA = tile->head; jetA != NULL; jetA = jetA->next) {//every jet in the tile
        for (jetB = tile->head; jetB != jetA; jetB = jetB->next) {
            double dist = _bj_dist(jetA,jetB);//Depending on the algorithm used, the distance has a different definition.
            //If the newly calculated distance is smaller than the registered one, update it.
            if (dist < jetA->NN_dist) {jetA->NN_dist = dist; jetA->NN = jetB;}
            if (dist < jetB->NN_dist) {jetB->NN_dist = dist; jetB->NN = jetA;}
        }
    }
    // then do it for RH (right hand) tiles
    for (Tile ** RTile = tile->RH_tiles; RTile != tile->end_tiles; RTile++) {//loop through all tiles to the right side
        for (jetA = tile->head; jetA != NULL; jetA = jetA->next) {//every jet in that tile
            for (jetB = (*RTile)->head; jetB != NULL; jetB = jetB->next) {
                double dist = _bj_dist(jetA,jetB);
                if (dist < jetA->NN_dist) {jetA->NN_dist = dist; jetA->NN = jetB;}
                if (dist < jetB->NN_dist) {jetB->NN_dist = dist; jetB->NN = jetA;}
            }
        }
}