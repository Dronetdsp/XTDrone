/**
 * @file /include/xtdrone_qt/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef xtdrone_qt_QNODE_HPP_
#define xtdrone_qt_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

// To workaround boost/qt4 problems that won't be bugfixed. Refer to
//    https://bugreports.qt.io/browse/QTBUG-22829
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif
#include <string>
#include <QThread>
#include <QStringListModel>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TwistStamped.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/String.h>
//#include <boost/bind.hpp>
#include <vector>


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace xtdrone_qt {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
    QNode(int argc, char** argv);
//    QNode(LISTINT multi_select, int *multi_num, QString *multi_type);
    virtual ~QNode();
    typedef QList<int> LISTINT;
    typedef QList<std::string> LISTSTR;
    typedef QList<geometry_msgs::Twist> LISTTWIST;
    typedef QList<std_msgs::String> LISTSTRR;
//	bool init();
//  init varibles
    LISTTWIST vel;
    LISTSTRR cmd;
    int multirotor_num = 0;
    LISTINT multirotor_get_control;
    LISTSTR multirotor_type;
    geometry_msgs::Pose local_pose[30];
    int * test;
    bool stop_flag;
    bool start_control_flag;
    bool ctrl_leader;
    bool cmd_vel_mask;
    bool cmd_change_flag;
    bool cmd_buffer;
    std::string control_type;
    // init functions
    bool init(const LISTINT multi_select, const int *multi_num, const LISTSTR multi_type, std::string control_type);
//	bool init(const std::string &master_url, const std::string &host_url);
    void set_cmd(double q_forward, double q_upward, double q_leftward, double q_orientation, bool q_ctrl_leader, std::string &q_cmd, bool q_cmd_vel_mask);
    void show_log();
    void start_control(bool q_start_control_flag);
    void stop_control(bool q_stop_flag);
    void get_uav_control(LISTINT multirotor_get_control);
    void run();



    /*********************
    ** Logging
    **********************/
    enum LogLevel {
             Debug,
             Info,
             Warn,
             Error,
             Fatal
     };

    QStringListModel* loggingModel() { return &logging_model; }
    void log( const LogLevel &level, const std::string &msg);

Q_SIGNALS:
    void loggingUpdated();
    void rosShutdown();
    void uavposition(float posi_x, float posi_y);

private:
    int init_argc;
    char** init_argv;
    ros::Publisher chatter_publisher;
//    ros::Publisher chatter_publisher_2;
    QStringListModel logging_model;
    std::vector<ros::Subscriber> buffer_multi_odom_groundtruth_sub;
    std::vector<ros::Subscriber> buffer_local_vel_sub;
    std::vector<ros::Publisher> buffer_multi_cmd_vel_flu_pub;
    std::vector<ros::Publisher> buffer_multi_cmd_pub;
    std::vector<ros::Publisher> buffer_multi_cmd_accel_flu_pub;
    ros::Publisher leader_cmd_vel_flu_pub;
    ros::Publisher leader_cmd_accel_flu_pub;
    ros::Publisher leader_cmd_pub;
    void publish();

};

}  // namespace xtdrone_qt

#endif /* xtdrone_qt_QNODE_HPP_ */