#pragma once
#include <CL/cl.hpp>

///<summary>denotes workload type</summary>
enum class RequirementType {
	ComputeHeavy,
	MemoryHeavy
};

///<summary>returns all devices which fits the device type and requirement type criteria, all belonging to one platfrom</summary>
///<returns>vectors of opencl devices</returns>
///<param name="dType">typeOf cl_device_type, denotes type of devices required</param>
///<param name="dType">typeOf enum class RequirementType, denotes workload type</param>
std::vector<cl::Device> getOptimalDevices(const cl_device_type dType, const RequirementType rType);
