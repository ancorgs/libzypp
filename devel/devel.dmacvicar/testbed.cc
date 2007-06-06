#include <sys/time.h>

#include <iostream>
#include <fstream>

#include <zypp/base/Logger.h>
#include <zypp/ZYpp.h>
#include <zypp/ZYppFactory.h>

#include "zypp/Product.h"
#include "zypp/detail/PackageImplIf.h"
#include "zypp/Package.h"
#include "zypp/RepositoryFactory.h"
#include "zypp/repo/cached/RepoImpl.h"
#include "zypp/data/ResolvableData.h"

using namespace std;
using namespace zypp;
using namespace zypp::repo;
using namespace zypp::repo::cached;


int main(int argc, char **argv)
{
    try
    {
      ZYpp::Ptr z = getZYpp();
    
      z->initializeTarget("/");
      ResStore res = z->target()->resolvables();
      MIL << res.size() << " resolvables" << endl;

    }
    catch ( const Exception &e )
    {
      ZYPP_CAUGHT(e);
      cout << e.msg() << endl;
    }
    
    return 0;
}



