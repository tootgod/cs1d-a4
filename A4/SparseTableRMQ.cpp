#include "SparseTableRMQ.h"

SparseTableRMQ::SparseTableRMQ(const RMQEntry* elems, std::size_t numElems) {
  logTable.reserve((numElems)+1);
  logTable.emplace_back(0);
  logTable.emplace_back(0);
  for (std::size_t i =2; i < numElems; i++)
  {
    logTable.emplace_back(logTable[i/2] + 1);
  }

  indexVector.reserve(logTable.back()+1);
  for(std::size_t i = 0; i < (logTable.back()+1); i = i + 1)
  {
     std::vector<std::size_t> row;
     indexVector.emplace_back(row);
  }
  
  array = elems;
  
  int q = 0;
  while(q == 0)
  {
    indexVector[0].reserve(numElems);
    for(std::size_t i = 0; i < numElems; i = i+1)
    {

      indexVector[0].emplace_back(i);
    }
    q++;
  }

  for(std::size_t i = 1; i < indexVector.size(); i = i+1)
  {    
    indexVector[i].reserve(numElems);
    for(std::size_t j = 0; j +(1<<i) <= numElems; j = j+1)
    {
        if(elems[indexVector[i-1][j]]<elems[indexVector[i-1][j+(1<<(i-1))]])
          {
            indexVector[i].emplace_back(indexVector[i-1][j]);
          }
        else
          {
            indexVector[i].emplace_back(indexVector[i-1][j+(1<<(i-1))]);
          }
    }
  //draw();
  }
  //draw();
}

SparseTableRMQ::~SparseTableRMQ() {
  indexVector.clear();
}

std::size_t SparseTableRMQ::rmq(std::size_t low, std::size_t high) const {
  std::size_t length = (high) - low;
  std::size_t row = logTable[length - 1];
  std::size_t highLog = logTable[length-1];
  

  if(1 == length)
  {
    return indexVector[row][low];
  }
  else if(array[indexVector[highLog][low]]<array[indexVector[highLog][high - (1 << highLog)]])
  {
    return indexVector[highLog][low];
  }
  else
  {
    return indexVector[highLog][high- (1 <<row)];
  }
  
}

void SparseTableRMQ::draw()
{
   for (std::size_t i = 0; i < indexVector.size(); i = i+1) {
        for (std::size_t j = 0; j < indexVector[i].size(); j = j+1)
            std::cout << indexVector[i][j] << " ";
        std::cout << std::endl;
}
}
