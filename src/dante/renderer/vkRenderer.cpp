#include <vulkan/vulkan.h>

VkResult vkInit() {
  VkApplicationInfo appInfo = {};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "WithinUs";
  appInfo.pEngineName = "Dante";

  VkInstanceCreateInfo instanceInfo = {};
  instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instanceInfo.pApplicationInfo = &appInfo;

  VkInstance instance;

  VkResult result = vkCreateInstance(&instanceInfo, 0, &instance);
  return result;
}