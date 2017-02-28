/**
 * @file /src/main.cpp
 *
 * @brief Qt based gui.
 *
 * @date November 2010
 **/
/*****************************************************************************
** Includes
*****************************************************************************/
#include "../include/wmr_ros/qnode.hpp"

/*****************************************************************************
** Main
*****************************************************************************/

int main(int argc, char **argv) {
    ros::init(argc,argv,"wmr_ros");
    wmr_ros::QNode *qnode = new wmr_ros::QNode();
    qnode->init();
    ros::waitForShutdown();

    return 0;
}
