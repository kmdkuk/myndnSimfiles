#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"
#include <string>

namespace ns3 {

  int main(int argc, char* argv[])
  {
    CommandLine cmd;
    cmd.Parse(argc, argv);

    AnnotatedTopologyReader topologyReader("", 10);
    topologyReader.SetFileName("scratch/topo-binary-tree-5tier.txt");
    topologyReader.Read();

    // ContentsStore information setting
    ndn::StackHelper ndnHelper;
    ndnHelper.SetOldContentStore("ns3::ndn::cs::Lfu", "MaxSize", "10");
    ndnHelper.InstallAll();

    ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
    ndnGlobalRoutingHelper.InstallAll();

    Ptr<Node> consumer = Names::Find<Node>("Src1");

    Ptr<Node> producer[8];
    for (int i=0;i<8;i++)
    {
      std::string name("Dst"+std::to_string(i+1));
      producer[i] = Names::Find<Node>(name);
    }

    Simulator::Stop(Seconds(20.0));

    Simulator::Run();
    Simulator::Destroy();

    return 0;
  }
}

int main(int argc, char* argv[])
{
  return ns3::main(argc, argv);
}
