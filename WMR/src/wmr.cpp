#include "include/wmr.h"


WMR::WMR(QCoreApplication *application):qapp_(application)
{

}

void WMR::spinOnce()
{
    qapp_->processEvents();
}
