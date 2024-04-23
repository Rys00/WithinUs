#include <vulkan/vulkan.h>
// #ifdef WINDOWS_BUILD
#include <vulkan/vulkan_win32.h>
// #endif
#include <iostream>

#define ArraySize(arr) sizeof((arr))/sizeof((arr[0]))

#define VK_CHECK(result)\
if(result != VK_SUCCESS) {\
  std::cout << "Vulkan error: " << result << std::endl;\
  __debugbreak();\
  return false;\
}

struct VkContext {
  VkInstance instance;
  VkSurfaceKHR surface;
  int graphicsIdx;
  VkPhysicalDevice gpu;
};

bool vkInit(VkContext* vkcontext, void* window) {
  VkApplicationInfo appInfo = {};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "WithinUs";
  appInfo.pEngineName = "Dante";

  char* extensions[] = {
// #ifdef WINDOWS_BUILD
    VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
// #endif
    VK_KHR_SURFACE_EXTENSION_NAME
  };

  VkInstanceCreateInfo instanceInfo = {};
  instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instanceInfo.pApplicationInfo = &appInfo;
  instanceInfo.ppEnabledExtensionNames = extensions;
  instanceInfo.enabledExtensionCount = ArraySize(extensions);
  VK_CHECK(vkCreateInstance(&instanceInfo, 0, &vkcontext->instance));

  {
// #ifdef WINDOWS_BUILD
    VkWin32SurfaceCreateInfoKHR surfaceInfo = {};
    surfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    surfaceInfo.hwnd = (HWND)window;
    surfaceInfo.hinstance = GetModuleHandleA(0);
    VK_CHECK(vkCreateWin32SurfaceKHR(vkcontext->instance, &surfaceInfo, 0, &vkcontext->surface));
// #endif
  }

  {
    vkcontext->graphicsIdx = -1;
    uint32_t gpuCount = 0;
    VkPhysicalDevice gpus[10];
    VK_CHECK(vkEnumeratePhysicalDevices(vkcontext->instance, &gpuCount, 0));
    VK_CHECK(vkEnumeratePhysicalDevices(vkcontext->instance, &gpuCount, gpus));

    for(uint32_t i = 0; i < gpuCount; ++i) {
      VkPhysicalDevice gpu = gpus[i];
      VkQueueFamilyProperties queueProps[10];
      uint32_t queueFamilyCount = 0;
      vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queueFamilyCount, 0);
      vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queueFamilyCount, queueProps);

      for(uint32_t j = 0; j < queueFamilyCount; ++j) {
        if(queueProps[j].queueFlags && VK_QUEUE_GRAPHICS_BIT) {
          VkBool32 surfaceSupport = VK_FALSE;
          VK_CHECK(vkGetPhysicalDeviceSurfaceSupportKHR(gpu, j, vkcontext->surface, &surfaceSupport));

          if(surfaceSupport) {
            vkcontext->graphicsIdx = j;
            vkcontext->gpu = gpu;
            break;
          }
        }
      }
    }
  }

  if(vkcontext->graphicsIdx < 0) {
    return false;
  }


  return true;
}