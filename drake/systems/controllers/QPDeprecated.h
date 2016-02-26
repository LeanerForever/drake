#ifndef QPDEPRECATED_H
#define QPDEPRECATED_H

#include "drake/solvers/gurobiQP.h"

const double REG = 1e-8;

struct QPControllerData {
  GRBenv *env;
  RigidBodyTree * r;
  double slack_limit; // maximum absolute magnitude of acceleration slack variable values
  Eigen::VectorXd umin,umax;
  void* map_ptr;
  std::set<int> active;

  // preallocate memory
  Eigen::MatrixXd H, H_float, H_act;
  Eigen::VectorXd C, C_float, C_act;
  Eigen::MatrixXd B, B_act;
  Eigen::MatrixXd J;
  Eigen::Vector3d Jdotv;
  Eigen::MatrixXd J_xy;
  Eigen::Vector2d Jdotv_xy;
  Eigen::MatrixXd Hqp;
  Eigen::RowVectorXd fqp;
  
  // momentum controller-specific
  Eigen::MatrixXd Ag; // centroidal momentum matrix
  Vector6d Agdot_times_v; // centroidal momentum velocity-dependent bias
  Eigen::MatrixXd Ak; // centroidal angular momentum matrix
  Eigen::Vector3d Akdot_times_v; // centroidal angular momentum velocity-dependent bias

  Eigen::MatrixXd W_kdot; // quadratic cost for angular momentum rate: (kdot_des - kdot)'*W*(kdot_des - kdot)
  Eigen::VectorXd w_qdd; 
  double w_grf; 
  double w_slack; 
  double Kp_ang; // angular momentum (k) P gain 
  double Kp_accel; // gain for support acceleration constraint: accel=-Kp_accel*vel

  int n_body_accel_inputs;
  int n_body_accel_eq_constraints;
  Eigen::VectorXd body_accel_input_weights;
  int n_body_accel_bounds;
  std::vector<int> accel_bound_body_idx;
  std::vector<Vector6d,Eigen::aligned_allocator<Vector6d>> min_body_acceleration;
  std::vector<Vector6d,Eigen::aligned_allocator<Vector6d>> max_body_acceleration;

  // gurobi active set params
  int *vbasis;
  int *cbasis;
  int vbasis_len;
  int cbasis_len;
};


#endif
