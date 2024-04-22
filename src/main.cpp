#include <iostream>
#include <vulkan/vulkan.h>

int main() {
  VkApplicationInfo appInfo = {};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "WithinUs";
  appInfo.pEngineName = "Dante";

  VkInstanceCreateInfo instanceInfo = {};
  instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instanceInfo.pApplicationInfo = &appInfo;

  VkInstance instance;

  VkResult result = vkCreateInstance(&instanceInfo, 0, &instance);
  if (result == VK_SUCCESS) {
    std::cout << "Successfully created vk instance!\n";
  }
  return 0;
}