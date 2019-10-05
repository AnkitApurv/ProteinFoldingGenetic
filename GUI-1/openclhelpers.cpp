#include "stdafx.h"

#include "openclhelpers.h"

///<summary>each vector of device represent individual platform</summary>
std::vector<std::vector<cl::Device>> getAllDevices(const cl_device_type dType) {
	//get all platforms
	std::vector<cl::Platform> allPlatforms;
	cl::Platform::get(&allPlatforms);

	//get all devices
	std::vector<std::vector<cl::Device>> allDevices;
	std::vector<cl::Device> tempDeviceList;
	for (cl::Platform p : allPlatforms) {
		p.getDevices(dType, &tempDeviceList);
		tempDeviceList.shrink_to_fit();
		allDevices.push_back(tempDeviceList);
	}
	allDevices.shrink_to_fit();
	return allDevices;
}

///<summary>last element of each integer vector is the sum of other elements in the vector, giving platform metric</summary>
std::vector<std::vector<uint32_t>> createMetric(const RequirementType rType, std::vector<std::vector<cl::Device>> allDevices) {
	std::vector<std::vector<uint32_t>> metrics;
	int currentDeviceMetric = 0, currentPlatformMetric = 0;
	for (int vd = 0; vd < allDevices.size(); vd++) {
		for (cl::Device d : allDevices[vd]) {
			switch (rType) {
			case RequirementType::ComputeHeavy:
				currentDeviceMetric = d.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() * d.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>();
			default:

				break;
			case RequirementType::MemoryHeavy:
				currentDeviceMetric = d.getInfo<CL_DEVICE_LOCAL_MEM_SIZE>() + d.getInfo<CL_DEVICE_GLOBAL_MEM_CACHE_SIZE>();
				break;
			}
			metrics[vd].push_back(currentDeviceMetric);
		}
		for (int n : metrics[vd]) {
			currentPlatformMetric += n;
		}
		metrics[vd].push_back(currentPlatformMetric);
	}

}

///<summary>
std::vector<cl::Device> getOptimalDevices(cl_device_type dType, RequirementType rType) {
	//all devices awailable on the system, platform-wise
	std::vector<std::vector<cl::Device>> allDevices = getAllDevices(dType);
	//metrics for all devices, last elemts are metrics for platform(i.e. sum of device metrics for that platform)
	std::vector<std::vector<uint32_t>> metrics = createMetric(rType, allDevices);

	//choosing vector of devices whose platform has best metrics
	int bestPlatformMetric = 0; int bestPlatformIndex = 0;
	for (uint32_t v = 0; v < metrics.size(); v++) {
		if (bestPlatformMetric < metrics[v].back()) {
			bestPlatformMetric = metrics[v].back();
			bestPlatformIndex = v;
		}
	}

	//vector of devices whose platform has best metrics
	std::vector<cl::Device> optimalPlatform = allDevices[bestPlatformIndex];
	optimalPlatform.shrink_to_fit();

	return optimalPlatform;
}
