#include "HybridRMQ.h"

HybridRMQ::HybridRMQ(const RMQEntry* elems, std::size_t numElems) {
  
  blockSize = round(sqrt(numElems));
  summary.reserve((numElems/blockSize) + 1);
  array = elems;
   std::size_t count = 0;
    std::size_t smallest = 0;
  for(std::size_t i = 0; i < numElems;i = i+1)
  {
  
    if(elems[i] < elems[smallest])
    {
      smallest = i;
    }
    count = count + 1;
    
    if(count == blockSize)
    {
      summary.emplace_back(smallest);
      smallest = i + 1;
      count = 0;
    }
    else if(i == numElems - 1)
    {
      summary.emplace_back(smallest);
    }
  }
} 

HybridRMQ::~HybridRMQ() {
 
}

std::size_t HybridRMQ::rmq(std::size_t low, std::size_t high) const {
  std::size_t lowBlock = ((low - (low%blockSize))/blockSize);
  std::size_t highBlock = (((high - 1) - ((high - 1)%blockSize))/blockSize);
  std::size_t smallest = low;

  //std::cout << arrayCpy[0] << std::endl;
  //std::cout << lowBlock << " " << highBlock << "//";

  //std::cout << blockSize << " " << low << " " << high;

  if(lowBlock == highBlock)
  {
    for(std::size_t i = low; i < high; i = i+1)
    {
      if(array[i] < array[smallest])
      {
        smallest = i;
      }
    }
    //std::cout << " a ";
  }
  else if(highBlock == lowBlock +1)
  {
  for(std::size_t i = low; i < high; i = i+1)
    {
      if(array[i] < array[smallest])
      {
        smallest = i;
      }
    }
   // std::cout << " b ";
  }
  else{
    //std::cout << "\n";
    for(std::size_t i = low; i < (((low - (low%blockSize)))+blockSize); i = i+1)
    {
      //std::cout << " " << array[i].value();
      if(array[i] < array[smallest])
      {
        smallest = i;
      }
    }
  
    for(std::size_t i = ((((low - (low%blockSize)+blockSize)/blockSize))); i < (((high) - ((high)%blockSize))/blockSize); i = i + 1)
    {
      //std::cout << " " << array[summary[i]].value();
      if(array[summary[i]] < array[smallest])
      {
        smallest = summary[i];
        
      }
    }

    
   // std::cout << " " << ((((low - (low%blockSize)+blockSize)/blockSize))) << " " << (((high) - ((high)%blockSize))/blockSize);
    for(std::size_t i = (high-1) - ((high-1)%blockSize); i < high; i = i+1)
    {
      //std::cout << " " << array[i].value();
      if(array[i] < array[smallest])
      {
        smallest = i;
      }
    }
   //std::cout << " c " << (((low - (low%blockSize)))) << " ";
  }
  //std::cout << smallest << "\n";
  return smallest;
}
