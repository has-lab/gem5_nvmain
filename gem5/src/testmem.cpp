#include<iostream>
#include "packet.hh"

using namespace std;
int main(void)
{
   PacketPtr pkt=new Packet();
   delete pkt;
   return 0;
}