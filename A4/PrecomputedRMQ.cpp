#include "PrecomputedRMQ.h"

PrecomputedRMQ::PrecomputedRMQ(const RMQEntry* elems, std::size_t numElems) {

  indexVector.reserve(numElems);
  for(std::size_t r = 0; r < numElems; r = r + 1)
     { 
      std::vector<std::size_t> row;
      row.reserve(numElems);
      for(std::size_t c = 0; c != r; c = c + 1)
      {
        row.emplace_back(600);
      }
      row.emplace_back(r);
      indexVector.emplace_back(row);
      }
      
    std::size_t numElems_SubOne = numElems - 1;
    for(std::size_t i = 0; i < numElems_SubOne; i = i + 1)
    {
      std::size_t safe = 0;
      for(std::size_t j = i; j < numElems_SubOne; j = j + 1)
      {
        if(elems[indexVector[safe][j]]<elems[indexVector[safe+1][j+1]])
          {
            indexVector[safe].emplace_back(indexVector[safe][j]);
          }
        else
          {
            indexVector[safe].emplace_back(indexVector[safe+1][j+1]);
          }
          safe = safe +1;
      }
  //draw();
  }
 //draw();
  
}

PrecomputedRMQ::~PrecomputedRMQ() {
  indexVector.clear();
}

std::size_t PrecomputedRMQ::rmq(std::size_t low, std::size_t high) const {
  
  //std::cout << "--------\n" << indexVector[low][high-1] << "\n" << low << " " << high << "\n";
  return indexVector[low][high-1];;
}

void PrecomputedRMQ::draw()
{
   for (std::size_t i = 0; i < indexVector.size(); i = i+1) {
        for (std::size_t j = 0; j < indexVector[i].size(); j = j+1)
            std::cout << indexVector[i][j] << " ";
        std::cout << std::endl;
}
}
