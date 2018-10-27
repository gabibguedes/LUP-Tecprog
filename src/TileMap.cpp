/*********************************************************
   * File: TileMap.cpp
   * Purpose: TileMap class implementation
*********************************************************/
#include "TileMap.h"
#include "Camera.h"

TileMap::TileMap(string file, TileSet* tileSet){
	Load(file);
	this->tileSet = tileSet;
}

void TileMap::Load(string file){
	FILE* fp;
	fp = fopen(file.c_str(),"r");
	fscanf(fp,"%d,",&mapWidth);
	fscanf(fp,"%d,",&mapHeight);
	fscanf(fp,"%d,",&mapDepth);
	int aux;
	while(!feof(fp)){
		fscanf(fp,"%d,",&aux);
		tileMatrix.emplace_back(aux-1);
	}
}

void TileMap::SetTileSet(TileSet* tileSet){
	this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z = 0){
	if(x>mapWidth || y>mapHeight || z > mapDepth){
		cout << "Wrong index!!" << endl;                                            
		exit(1);
	}
	int aux = (z*(mapWidth*mapHeight)) + (y*mapWidth) + x;
	return tileMatrix[aux];
}

void TileMap::RenderLayer(int layer, int cameraX = 0, int cameraY = 0){
	for(int i=0;i<mapHeight;i++){
		for(int j=0;j<mapWidth;j++){
			int aux = At(j,i,layer);
			if(aux >= 0){
        float positionX = j*tileSet->GetTileWidth() + cameraX*(layer+1);        
        float positionY = i*tileSet->GetTileHeight() + cameraY*(layer+1);       
				tileSet->Render(aux, positionX ,positionY);                             
			}
		}
	}
}

void TileMap::Render(int cameraX,int cameraY){
	for(int i=1;i<mapDepth;i++){
		RenderLayer(i,cameraX,cameraY);
	}
}

int TileMap::GetWidth(){
	return mapWidth;
}

int TileMap::GetHeight(){
	return mapHeight;
}

int TileMap::GetDepth(){
	return mapDepth;
}
