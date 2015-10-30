#include <iostream>
#include <string>
#include "DLL.h"
#include "../logging/Log.h"
#include <sstream>

using namespace std;

int main()
{
  //initialize errorLogging object
  Log* p_log = new Log;

  //helper objects for converting ints to strings
  string intStr;
  ostringstream convert;

  //create dll object for testing
  p_log->info("DLL pointer 'p_DLL' acessing DLL object");
  DLL <string>* p_DLL = new DLL <string> (p_log);

  p_log->info("***Testing insertAtFront function***");
  p_DLL->insertAtFront("hello");
  p_DLL->insertAtFront("brave");
  p_DLL->insertAtFront("new");
  p_DLL->insertAtFront("world");

  p_log->info("***Testing printAllFromHeadFunction***");
  p_DLL->printAllFromHead();

  p_log->info("***Testing printAllFromTailFunction***");
  p_DLL->printAllFromTail();

  p_log->info("***Note***");
  p_log->info("first(),last(),next(),and previous tested in printAll functions");

  p_log->info("***Testing insertAtRear function***");

  p_DLL->insertAtRear("a");
  p_DLL->insertAtRear("strange");
  p_DLL->insertAtRear("world");
  p_DLL->insertAtRear("it");
  p_DLL->insertAtRear("is");
  p_log->info("***printAllFromHead()***");
  p_DLL->printAllFromHead();
  p_log->info("***printAllFromTail()***");
  p_DLL->printAllFromTail();
  
  p_log->info("***Testing size function***");

  //find size, convert to string
  int size = p_DLL->size();
  convert << size;
  intStr = convert.str();

  p_log->info("Size of dll right now: " + intStr);

  p_log->info("***Testing removeFromFront function***");
  
  //string helper variable
  string cheese;

  p_DLL->removeFromFront(cheese);
  p_log->info("Element removed: " + cheese + " ...");
  p_DLL->removeFromFront(cheese);
  p_log->info("Element removed: " + cheese + " ...");
  p_DLL->removeFromFront(cheese);
  p_log->info("Element removed: " + cheese + " ...");
  p_DLL->removeFromFront(cheese);
  p_log->info("Element removed: " + cheese + " ...");
  
  p_log->info("removeFromFront called four times...");

  p_DLL->printAllFromHead();

  p_log->info("***Testing removeFromRearFunction***");

  p_DLL->removeFromRear(cheese);
  p_log->info("Element removed: " + cheese + " ...");
  p_DLL->removeFromRear(cheese);
  p_log->info("Element removed: " + cheese + " ...");
  p_DLL->removeFromRear(cheese);
  p_log->info("Element removed: " + cheese + " ...");
  p_DLL->removeFromRear(cheese);
  p_log->info("Element removed: " + cheese + " ...");
  p_DLL->removeFromRear(cheese);
  p_log->info("Element removed: " + cheese + " ...");
  p_DLL->removeFromRear(cheese);
  p_log->info("Element removed: " + cheese + " ...");
  p_DLL->removeFromRear(cheese);
  
  p_log->info("removeFromRear called seven times...");

  p_DLL->printAllFromHead();

  delete p_DLL;

  return 0;
}

