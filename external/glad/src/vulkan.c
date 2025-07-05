/**
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/vulkan.h>

#ifndef GLAD_IMPL_UTIL_C_
#define GLAD_IMPL_UTIL_C_

#ifdef _MSC_VER
#define GLAD_IMPL_UTIL_SSCANF sscanf_s
#else
#define GLAD_IMPL_UTIL_SSCANF sscanf
#endif

#endif /* GLAD_IMPL_UTIL_C_ */

#ifdef __cplusplus
extern "C" {
#endif



int GLAD_VK_VERSION_1_0 = 0;
int GLAD_VK_VERSION_1_1 = 0;
int GLAD_VK_VERSION_1_2 = 0;
int GLAD_VK_VERSION_1_3 = 0;
int GLAD_VK_VERSION_1_4 = 0;
int GLAD_VK_AMD_draw_indirect_count = 0;
int GLAD_VK_EXT_buffer_device_address = 0;
int GLAD_VK_EXT_extended_dynamic_state = 0;
int GLAD_VK_EXT_extended_dynamic_state2 = 0;
int GLAD_VK_EXT_host_image_copy = 0;
int GLAD_VK_EXT_host_query_reset = 0;
int GLAD_VK_EXT_image_compression_control = 0;
int GLAD_VK_EXT_line_rasterization = 0;
int GLAD_VK_EXT_private_data = 0;
int GLAD_VK_EXT_shader_object = 0;
int GLAD_VK_EXT_tooling_info = 0;
int GLAD_VK_KHR_bind_memory2 = 0;
int GLAD_VK_KHR_buffer_device_address = 0;
int GLAD_VK_KHR_copy_commands2 = 0;
int GLAD_VK_KHR_create_renderpass2 = 0;
int GLAD_VK_KHR_descriptor_update_template = 0;
int GLAD_VK_KHR_device_group = 0;
int GLAD_VK_KHR_device_group_creation = 0;
int GLAD_VK_KHR_draw_indirect_count = 0;
int GLAD_VK_KHR_dynamic_rendering = 0;
int GLAD_VK_KHR_dynamic_rendering_local_read = 0;
int GLAD_VK_KHR_external_fence_capabilities = 0;
int GLAD_VK_KHR_external_memory_capabilities = 0;
int GLAD_VK_KHR_external_semaphore_capabilities = 0;
int GLAD_VK_KHR_get_memory_requirements2 = 0;
int GLAD_VK_KHR_get_physical_device_properties2 = 0;
int GLAD_VK_KHR_line_rasterization = 0;
int GLAD_VK_KHR_maintenance1 = 0;
int GLAD_VK_KHR_maintenance3 = 0;
int GLAD_VK_KHR_maintenance4 = 0;
int GLAD_VK_KHR_maintenance5 = 0;
int GLAD_VK_KHR_maintenance6 = 0;
int GLAD_VK_KHR_map_memory2 = 0;
int GLAD_VK_KHR_push_descriptor = 0;
int GLAD_VK_KHR_sampler_ycbcr_conversion = 0;
int GLAD_VK_KHR_synchronization2 = 0;
int GLAD_VK_KHR_timeline_semaphore = 0;


static void _pre_call_vulkan_callback_default(const char *name, GLADapiproc apiproc, int len_args, ...) {
    GLAD_UNUSED(name);
    GLAD_UNUSED(apiproc);
    GLAD_UNUSED(len_args);
}
static void _post_call_vulkan_callback_default(void *ret, const char *name, GLADapiproc apiproc, int len_args, ...) {
    GLAD_UNUSED(ret);
    GLAD_UNUSED(name);
    GLAD_UNUSED(apiproc);
    GLAD_UNUSED(len_args);
}

static GLADprecallback _pre_call_vulkan_callback = _pre_call_vulkan_callback_default;
void gladSetVulkanPreCallback(GLADprecallback cb) {
    _pre_call_vulkan_callback = cb;
}
static GLADpostcallback _post_call_vulkan_callback = _post_call_vulkan_callback_default;
void gladSetVulkanPostCallback(GLADpostcallback cb) {
    _post_call_vulkan_callback = cb;
}

PFN_vkAcquireNextImage2KHR glad_vkAcquireNextImage2KHR = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkAcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR * pAcquireInfo, uint32_t * pImageIndex) {
    VkResult ret;
    _pre_call_vulkan_callback("vkAcquireNextImage2KHR", (GLADapiproc) glad_vkAcquireNextImage2KHR, 3, device, pAcquireInfo, pImageIndex);
    ret = glad_vkAcquireNextImage2KHR(device, pAcquireInfo, pImageIndex);
    _post_call_vulkan_callback((void*) &ret, "vkAcquireNextImage2KHR", (GLADapiproc) glad_vkAcquireNextImage2KHR, 3, device, pAcquireInfo, pImageIndex);
    return ret;
}
PFN_vkAcquireNextImage2KHR glad_debug_vkAcquireNextImage2KHR = glad_debug_impl_vkAcquireNextImage2KHR;
PFN_vkAllocateCommandBuffers glad_vkAllocateCommandBuffers = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkAllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo * pAllocateInfo, VkCommandBuffer * pCommandBuffers) {
    VkResult ret;
    _pre_call_vulkan_callback("vkAllocateCommandBuffers", (GLADapiproc) glad_vkAllocateCommandBuffers, 3, device, pAllocateInfo, pCommandBuffers);
    ret = glad_vkAllocateCommandBuffers(device, pAllocateInfo, pCommandBuffers);
    _post_call_vulkan_callback((void*) &ret, "vkAllocateCommandBuffers", (GLADapiproc) glad_vkAllocateCommandBuffers, 3, device, pAllocateInfo, pCommandBuffers);
    return ret;
}
PFN_vkAllocateCommandBuffers glad_debug_vkAllocateCommandBuffers = glad_debug_impl_vkAllocateCommandBuffers;
PFN_vkAllocateDescriptorSets glad_vkAllocateDescriptorSets = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkAllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo * pAllocateInfo, VkDescriptorSet * pDescriptorSets) {
    VkResult ret;
    _pre_call_vulkan_callback("vkAllocateDescriptorSets", (GLADapiproc) glad_vkAllocateDescriptorSets, 3, device, pAllocateInfo, pDescriptorSets);
    ret = glad_vkAllocateDescriptorSets(device, pAllocateInfo, pDescriptorSets);
    _post_call_vulkan_callback((void*) &ret, "vkAllocateDescriptorSets", (GLADapiproc) glad_vkAllocateDescriptorSets, 3, device, pAllocateInfo, pDescriptorSets);
    return ret;
}
PFN_vkAllocateDescriptorSets glad_debug_vkAllocateDescriptorSets = glad_debug_impl_vkAllocateDescriptorSets;
PFN_vkAllocateMemory glad_vkAllocateMemory = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkAllocateMemory(VkDevice device, const VkMemoryAllocateInfo * pAllocateInfo, const VkAllocationCallbacks * pAllocator, VkDeviceMemory * pMemory) {
    VkResult ret;
    _pre_call_vulkan_callback("vkAllocateMemory", (GLADapiproc) glad_vkAllocateMemory, 4, device, pAllocateInfo, pAllocator, pMemory);
    ret = glad_vkAllocateMemory(device, pAllocateInfo, pAllocator, pMemory);
    _post_call_vulkan_callback((void*) &ret, "vkAllocateMemory", (GLADapiproc) glad_vkAllocateMemory, 4, device, pAllocateInfo, pAllocator, pMemory);
    return ret;
}
PFN_vkAllocateMemory glad_debug_vkAllocateMemory = glad_debug_impl_vkAllocateMemory;
PFN_vkBeginCommandBuffer glad_vkBeginCommandBuffer = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkBeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo * pBeginInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkBeginCommandBuffer", (GLADapiproc) glad_vkBeginCommandBuffer, 2, commandBuffer, pBeginInfo);
    ret = glad_vkBeginCommandBuffer(commandBuffer, pBeginInfo);
    _post_call_vulkan_callback((void*) &ret, "vkBeginCommandBuffer", (GLADapiproc) glad_vkBeginCommandBuffer, 2, commandBuffer, pBeginInfo);
    return ret;
}
PFN_vkBeginCommandBuffer glad_debug_vkBeginCommandBuffer = glad_debug_impl_vkBeginCommandBuffer;
PFN_vkBindBufferMemory glad_vkBindBufferMemory = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkBindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) {
    VkResult ret;
    _pre_call_vulkan_callback("vkBindBufferMemory", (GLADapiproc) glad_vkBindBufferMemory, 4, device, buffer, memory, memoryOffset);
    ret = glad_vkBindBufferMemory(device, buffer, memory, memoryOffset);
    _post_call_vulkan_callback((void*) &ret, "vkBindBufferMemory", (GLADapiproc) glad_vkBindBufferMemory, 4, device, buffer, memory, memoryOffset);
    return ret;
}
PFN_vkBindBufferMemory glad_debug_vkBindBufferMemory = glad_debug_impl_vkBindBufferMemory;
PFN_vkBindBufferMemory2 glad_vkBindBufferMemory2 = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkBindBufferMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo * pBindInfos) {
    VkResult ret;
    _pre_call_vulkan_callback("vkBindBufferMemory2", (GLADapiproc) glad_vkBindBufferMemory2, 3, device, bindInfoCount, pBindInfos);
    ret = glad_vkBindBufferMemory2(device, bindInfoCount, pBindInfos);
    _post_call_vulkan_callback((void*) &ret, "vkBindBufferMemory2", (GLADapiproc) glad_vkBindBufferMemory2, 3, device, bindInfoCount, pBindInfos);
    return ret;
}
PFN_vkBindBufferMemory2 glad_debug_vkBindBufferMemory2 = glad_debug_impl_vkBindBufferMemory2;
PFN_vkBindBufferMemory2KHR glad_vkBindBufferMemory2KHR = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkBindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo * pBindInfos) {
    VkResult ret;
    _pre_call_vulkan_callback("vkBindBufferMemory2KHR", (GLADapiproc) glad_vkBindBufferMemory2KHR, 3, device, bindInfoCount, pBindInfos);
    ret = glad_vkBindBufferMemory2KHR(device, bindInfoCount, pBindInfos);
    _post_call_vulkan_callback((void*) &ret, "vkBindBufferMemory2KHR", (GLADapiproc) glad_vkBindBufferMemory2KHR, 3, device, bindInfoCount, pBindInfos);
    return ret;
}
PFN_vkBindBufferMemory2KHR glad_debug_vkBindBufferMemory2KHR = glad_debug_impl_vkBindBufferMemory2KHR;
PFN_vkBindImageMemory glad_vkBindImageMemory = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkBindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) {
    VkResult ret;
    _pre_call_vulkan_callback("vkBindImageMemory", (GLADapiproc) glad_vkBindImageMemory, 4, device, image, memory, memoryOffset);
    ret = glad_vkBindImageMemory(device, image, memory, memoryOffset);
    _post_call_vulkan_callback((void*) &ret, "vkBindImageMemory", (GLADapiproc) glad_vkBindImageMemory, 4, device, image, memory, memoryOffset);
    return ret;
}
PFN_vkBindImageMemory glad_debug_vkBindImageMemory = glad_debug_impl_vkBindImageMemory;
PFN_vkBindImageMemory2 glad_vkBindImageMemory2 = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkBindImageMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo * pBindInfos) {
    VkResult ret;
    _pre_call_vulkan_callback("vkBindImageMemory2", (GLADapiproc) glad_vkBindImageMemory2, 3, device, bindInfoCount, pBindInfos);
    ret = glad_vkBindImageMemory2(device, bindInfoCount, pBindInfos);
    _post_call_vulkan_callback((void*) &ret, "vkBindImageMemory2", (GLADapiproc) glad_vkBindImageMemory2, 3, device, bindInfoCount, pBindInfos);
    return ret;
}
PFN_vkBindImageMemory2 glad_debug_vkBindImageMemory2 = glad_debug_impl_vkBindImageMemory2;
PFN_vkBindImageMemory2KHR glad_vkBindImageMemory2KHR = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkBindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo * pBindInfos) {
    VkResult ret;
    _pre_call_vulkan_callback("vkBindImageMemory2KHR", (GLADapiproc) glad_vkBindImageMemory2KHR, 3, device, bindInfoCount, pBindInfos);
    ret = glad_vkBindImageMemory2KHR(device, bindInfoCount, pBindInfos);
    _post_call_vulkan_callback((void*) &ret, "vkBindImageMemory2KHR", (GLADapiproc) glad_vkBindImageMemory2KHR, 3, device, bindInfoCount, pBindInfos);
    return ret;
}
PFN_vkBindImageMemory2KHR glad_debug_vkBindImageMemory2KHR = glad_debug_impl_vkBindImageMemory2KHR;
PFN_vkCmdBeginQuery glad_vkCmdBeginQuery = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) {
    _pre_call_vulkan_callback("vkCmdBeginQuery", (GLADapiproc) glad_vkCmdBeginQuery, 4, commandBuffer, queryPool, query, flags);
    glad_vkCmdBeginQuery(commandBuffer, queryPool, query, flags);
    _post_call_vulkan_callback(NULL, "vkCmdBeginQuery", (GLADapiproc) glad_vkCmdBeginQuery, 4, commandBuffer, queryPool, query, flags);
    
}
PFN_vkCmdBeginQuery glad_debug_vkCmdBeginQuery = glad_debug_impl_vkCmdBeginQuery;
PFN_vkCmdBeginRenderPass glad_vkCmdBeginRenderPass = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo * pRenderPassBegin, VkSubpassContents contents) {
    _pre_call_vulkan_callback("vkCmdBeginRenderPass", (GLADapiproc) glad_vkCmdBeginRenderPass, 3, commandBuffer, pRenderPassBegin, contents);
    glad_vkCmdBeginRenderPass(commandBuffer, pRenderPassBegin, contents);
    _post_call_vulkan_callback(NULL, "vkCmdBeginRenderPass", (GLADapiproc) glad_vkCmdBeginRenderPass, 3, commandBuffer, pRenderPassBegin, contents);
    
}
PFN_vkCmdBeginRenderPass glad_debug_vkCmdBeginRenderPass = glad_debug_impl_vkCmdBeginRenderPass;
PFN_vkCmdBeginRenderPass2 glad_vkCmdBeginRenderPass2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo * pRenderPassBegin, const VkSubpassBeginInfo * pSubpassBeginInfo) {
    _pre_call_vulkan_callback("vkCmdBeginRenderPass2", (GLADapiproc) glad_vkCmdBeginRenderPass2, 3, commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
    glad_vkCmdBeginRenderPass2(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
    _post_call_vulkan_callback(NULL, "vkCmdBeginRenderPass2", (GLADapiproc) glad_vkCmdBeginRenderPass2, 3, commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
    
}
PFN_vkCmdBeginRenderPass2 glad_debug_vkCmdBeginRenderPass2 = glad_debug_impl_vkCmdBeginRenderPass2;
PFN_vkCmdBeginRenderPass2KHR glad_vkCmdBeginRenderPass2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBeginRenderPass2KHR(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo * pRenderPassBegin, const VkSubpassBeginInfo * pSubpassBeginInfo) {
    _pre_call_vulkan_callback("vkCmdBeginRenderPass2KHR", (GLADapiproc) glad_vkCmdBeginRenderPass2KHR, 3, commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
    glad_vkCmdBeginRenderPass2KHR(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
    _post_call_vulkan_callback(NULL, "vkCmdBeginRenderPass2KHR", (GLADapiproc) glad_vkCmdBeginRenderPass2KHR, 3, commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
    
}
PFN_vkCmdBeginRenderPass2KHR glad_debug_vkCmdBeginRenderPass2KHR = glad_debug_impl_vkCmdBeginRenderPass2KHR;
PFN_vkCmdBeginRendering glad_vkCmdBeginRendering = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBeginRendering(VkCommandBuffer commandBuffer, const VkRenderingInfo * pRenderingInfo) {
    _pre_call_vulkan_callback("vkCmdBeginRendering", (GLADapiproc) glad_vkCmdBeginRendering, 2, commandBuffer, pRenderingInfo);
    glad_vkCmdBeginRendering(commandBuffer, pRenderingInfo);
    _post_call_vulkan_callback(NULL, "vkCmdBeginRendering", (GLADapiproc) glad_vkCmdBeginRendering, 2, commandBuffer, pRenderingInfo);
    
}
PFN_vkCmdBeginRendering glad_debug_vkCmdBeginRendering = glad_debug_impl_vkCmdBeginRendering;
PFN_vkCmdBeginRenderingKHR glad_vkCmdBeginRenderingKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBeginRenderingKHR(VkCommandBuffer commandBuffer, const VkRenderingInfo * pRenderingInfo) {
    _pre_call_vulkan_callback("vkCmdBeginRenderingKHR", (GLADapiproc) glad_vkCmdBeginRenderingKHR, 2, commandBuffer, pRenderingInfo);
    glad_vkCmdBeginRenderingKHR(commandBuffer, pRenderingInfo);
    _post_call_vulkan_callback(NULL, "vkCmdBeginRenderingKHR", (GLADapiproc) glad_vkCmdBeginRenderingKHR, 2, commandBuffer, pRenderingInfo);
    
}
PFN_vkCmdBeginRenderingKHR glad_debug_vkCmdBeginRenderingKHR = glad_debug_impl_vkCmdBeginRenderingKHR;
PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT glad_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT(VkCommandBuffer commandBuffer, const VkBindDescriptorBufferEmbeddedSamplersInfoEXT * pBindDescriptorBufferEmbeddedSamplersInfo) {
    _pre_call_vulkan_callback("vkCmdBindDescriptorBufferEmbeddedSamplers2EXT", (GLADapiproc) glad_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT, 2, commandBuffer, pBindDescriptorBufferEmbeddedSamplersInfo);
    glad_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT(commandBuffer, pBindDescriptorBufferEmbeddedSamplersInfo);
    _post_call_vulkan_callback(NULL, "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT", (GLADapiproc) glad_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT, 2, commandBuffer, pBindDescriptorBufferEmbeddedSamplersInfo);
    
}
PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT glad_debug_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT = glad_debug_impl_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT;
PFN_vkCmdBindDescriptorSets glad_vkCmdBindDescriptorSets = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet * pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t * pDynamicOffsets) {
    _pre_call_vulkan_callback("vkCmdBindDescriptorSets", (GLADapiproc) glad_vkCmdBindDescriptorSets, 8, commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
    glad_vkCmdBindDescriptorSets(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
    _post_call_vulkan_callback(NULL, "vkCmdBindDescriptorSets", (GLADapiproc) glad_vkCmdBindDescriptorSets, 8, commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
    
}
PFN_vkCmdBindDescriptorSets glad_debug_vkCmdBindDescriptorSets = glad_debug_impl_vkCmdBindDescriptorSets;
PFN_vkCmdBindDescriptorSets2 glad_vkCmdBindDescriptorSets2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBindDescriptorSets2(VkCommandBuffer commandBuffer, const VkBindDescriptorSetsInfo * pBindDescriptorSetsInfo) {
    _pre_call_vulkan_callback("vkCmdBindDescriptorSets2", (GLADapiproc) glad_vkCmdBindDescriptorSets2, 2, commandBuffer, pBindDescriptorSetsInfo);
    glad_vkCmdBindDescriptorSets2(commandBuffer, pBindDescriptorSetsInfo);
    _post_call_vulkan_callback(NULL, "vkCmdBindDescriptorSets2", (GLADapiproc) glad_vkCmdBindDescriptorSets2, 2, commandBuffer, pBindDescriptorSetsInfo);
    
}
PFN_vkCmdBindDescriptorSets2 glad_debug_vkCmdBindDescriptorSets2 = glad_debug_impl_vkCmdBindDescriptorSets2;
PFN_vkCmdBindDescriptorSets2KHR glad_vkCmdBindDescriptorSets2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBindDescriptorSets2KHR(VkCommandBuffer commandBuffer, const VkBindDescriptorSetsInfo * pBindDescriptorSetsInfo) {
    _pre_call_vulkan_callback("vkCmdBindDescriptorSets2KHR", (GLADapiproc) glad_vkCmdBindDescriptorSets2KHR, 2, commandBuffer, pBindDescriptorSetsInfo);
    glad_vkCmdBindDescriptorSets2KHR(commandBuffer, pBindDescriptorSetsInfo);
    _post_call_vulkan_callback(NULL, "vkCmdBindDescriptorSets2KHR", (GLADapiproc) glad_vkCmdBindDescriptorSets2KHR, 2, commandBuffer, pBindDescriptorSetsInfo);
    
}
PFN_vkCmdBindDescriptorSets2KHR glad_debug_vkCmdBindDescriptorSets2KHR = glad_debug_impl_vkCmdBindDescriptorSets2KHR;
PFN_vkCmdBindIndexBuffer glad_vkCmdBindIndexBuffer = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) {
    _pre_call_vulkan_callback("vkCmdBindIndexBuffer", (GLADapiproc) glad_vkCmdBindIndexBuffer, 4, commandBuffer, buffer, offset, indexType);
    glad_vkCmdBindIndexBuffer(commandBuffer, buffer, offset, indexType);
    _post_call_vulkan_callback(NULL, "vkCmdBindIndexBuffer", (GLADapiproc) glad_vkCmdBindIndexBuffer, 4, commandBuffer, buffer, offset, indexType);
    
}
PFN_vkCmdBindIndexBuffer glad_debug_vkCmdBindIndexBuffer = glad_debug_impl_vkCmdBindIndexBuffer;
PFN_vkCmdBindIndexBuffer2 glad_vkCmdBindIndexBuffer2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBindIndexBuffer2(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, VkIndexType indexType) {
    _pre_call_vulkan_callback("vkCmdBindIndexBuffer2", (GLADapiproc) glad_vkCmdBindIndexBuffer2, 5, commandBuffer, buffer, offset, size, indexType);
    glad_vkCmdBindIndexBuffer2(commandBuffer, buffer, offset, size, indexType);
    _post_call_vulkan_callback(NULL, "vkCmdBindIndexBuffer2", (GLADapiproc) glad_vkCmdBindIndexBuffer2, 5, commandBuffer, buffer, offset, size, indexType);
    
}
PFN_vkCmdBindIndexBuffer2 glad_debug_vkCmdBindIndexBuffer2 = glad_debug_impl_vkCmdBindIndexBuffer2;
PFN_vkCmdBindIndexBuffer2KHR glad_vkCmdBindIndexBuffer2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBindIndexBuffer2KHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, VkIndexType indexType) {
    _pre_call_vulkan_callback("vkCmdBindIndexBuffer2KHR", (GLADapiproc) glad_vkCmdBindIndexBuffer2KHR, 5, commandBuffer, buffer, offset, size, indexType);
    glad_vkCmdBindIndexBuffer2KHR(commandBuffer, buffer, offset, size, indexType);
    _post_call_vulkan_callback(NULL, "vkCmdBindIndexBuffer2KHR", (GLADapiproc) glad_vkCmdBindIndexBuffer2KHR, 5, commandBuffer, buffer, offset, size, indexType);
    
}
PFN_vkCmdBindIndexBuffer2KHR glad_debug_vkCmdBindIndexBuffer2KHR = glad_debug_impl_vkCmdBindIndexBuffer2KHR;
PFN_vkCmdBindPipeline glad_vkCmdBindPipeline = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) {
    _pre_call_vulkan_callback("vkCmdBindPipeline", (GLADapiproc) glad_vkCmdBindPipeline, 3, commandBuffer, pipelineBindPoint, pipeline);
    glad_vkCmdBindPipeline(commandBuffer, pipelineBindPoint, pipeline);
    _post_call_vulkan_callback(NULL, "vkCmdBindPipeline", (GLADapiproc) glad_vkCmdBindPipeline, 3, commandBuffer, pipelineBindPoint, pipeline);
    
}
PFN_vkCmdBindPipeline glad_debug_vkCmdBindPipeline = glad_debug_impl_vkCmdBindPipeline;
PFN_vkCmdBindShadersEXT glad_vkCmdBindShadersEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBindShadersEXT(VkCommandBuffer commandBuffer, uint32_t stageCount, const VkShaderStageFlagBits * pStages, const VkShaderEXT * pShaders) {
    _pre_call_vulkan_callback("vkCmdBindShadersEXT", (GLADapiproc) glad_vkCmdBindShadersEXT, 4, commandBuffer, stageCount, pStages, pShaders);
    glad_vkCmdBindShadersEXT(commandBuffer, stageCount, pStages, pShaders);
    _post_call_vulkan_callback(NULL, "vkCmdBindShadersEXT", (GLADapiproc) glad_vkCmdBindShadersEXT, 4, commandBuffer, stageCount, pStages, pShaders);
    
}
PFN_vkCmdBindShadersEXT glad_debug_vkCmdBindShadersEXT = glad_debug_impl_vkCmdBindShadersEXT;
PFN_vkCmdBindVertexBuffers glad_vkCmdBindVertexBuffers = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer * pBuffers, const VkDeviceSize * pOffsets) {
    _pre_call_vulkan_callback("vkCmdBindVertexBuffers", (GLADapiproc) glad_vkCmdBindVertexBuffers, 5, commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
    glad_vkCmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
    _post_call_vulkan_callback(NULL, "vkCmdBindVertexBuffers", (GLADapiproc) glad_vkCmdBindVertexBuffers, 5, commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
    
}
PFN_vkCmdBindVertexBuffers glad_debug_vkCmdBindVertexBuffers = glad_debug_impl_vkCmdBindVertexBuffers;
PFN_vkCmdBindVertexBuffers2 glad_vkCmdBindVertexBuffers2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBindVertexBuffers2(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer * pBuffers, const VkDeviceSize * pOffsets, const VkDeviceSize * pSizes, const VkDeviceSize * pStrides) {
    _pre_call_vulkan_callback("vkCmdBindVertexBuffers2", (GLADapiproc) glad_vkCmdBindVertexBuffers2, 7, commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
    glad_vkCmdBindVertexBuffers2(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
    _post_call_vulkan_callback(NULL, "vkCmdBindVertexBuffers2", (GLADapiproc) glad_vkCmdBindVertexBuffers2, 7, commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
    
}
PFN_vkCmdBindVertexBuffers2 glad_debug_vkCmdBindVertexBuffers2 = glad_debug_impl_vkCmdBindVertexBuffers2;
PFN_vkCmdBindVertexBuffers2EXT glad_vkCmdBindVertexBuffers2EXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBindVertexBuffers2EXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer * pBuffers, const VkDeviceSize * pOffsets, const VkDeviceSize * pSizes, const VkDeviceSize * pStrides) {
    _pre_call_vulkan_callback("vkCmdBindVertexBuffers2EXT", (GLADapiproc) glad_vkCmdBindVertexBuffers2EXT, 7, commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
    glad_vkCmdBindVertexBuffers2EXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
    _post_call_vulkan_callback(NULL, "vkCmdBindVertexBuffers2EXT", (GLADapiproc) glad_vkCmdBindVertexBuffers2EXT, 7, commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
    
}
PFN_vkCmdBindVertexBuffers2EXT glad_debug_vkCmdBindVertexBuffers2EXT = glad_debug_impl_vkCmdBindVertexBuffers2EXT;
PFN_vkCmdBlitImage glad_vkCmdBlitImage = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit * pRegions, VkFilter filter) {
    _pre_call_vulkan_callback("vkCmdBlitImage", (GLADapiproc) glad_vkCmdBlitImage, 8, commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
    glad_vkCmdBlitImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
    _post_call_vulkan_callback(NULL, "vkCmdBlitImage", (GLADapiproc) glad_vkCmdBlitImage, 8, commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
    
}
PFN_vkCmdBlitImage glad_debug_vkCmdBlitImage = glad_debug_impl_vkCmdBlitImage;
PFN_vkCmdBlitImage2 glad_vkCmdBlitImage2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBlitImage2(VkCommandBuffer commandBuffer, const VkBlitImageInfo2 * pBlitImageInfo) {
    _pre_call_vulkan_callback("vkCmdBlitImage2", (GLADapiproc) glad_vkCmdBlitImage2, 2, commandBuffer, pBlitImageInfo);
    glad_vkCmdBlitImage2(commandBuffer, pBlitImageInfo);
    _post_call_vulkan_callback(NULL, "vkCmdBlitImage2", (GLADapiproc) glad_vkCmdBlitImage2, 2, commandBuffer, pBlitImageInfo);
    
}
PFN_vkCmdBlitImage2 glad_debug_vkCmdBlitImage2 = glad_debug_impl_vkCmdBlitImage2;
PFN_vkCmdBlitImage2KHR glad_vkCmdBlitImage2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdBlitImage2KHR(VkCommandBuffer commandBuffer, const VkBlitImageInfo2 * pBlitImageInfo) {
    _pre_call_vulkan_callback("vkCmdBlitImage2KHR", (GLADapiproc) glad_vkCmdBlitImage2KHR, 2, commandBuffer, pBlitImageInfo);
    glad_vkCmdBlitImage2KHR(commandBuffer, pBlitImageInfo);
    _post_call_vulkan_callback(NULL, "vkCmdBlitImage2KHR", (GLADapiproc) glad_vkCmdBlitImage2KHR, 2, commandBuffer, pBlitImageInfo);
    
}
PFN_vkCmdBlitImage2KHR glad_debug_vkCmdBlitImage2KHR = glad_debug_impl_vkCmdBlitImage2KHR;
PFN_vkCmdClearAttachments glad_vkCmdClearAttachments = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment * pAttachments, uint32_t rectCount, const VkClearRect * pRects) {
    _pre_call_vulkan_callback("vkCmdClearAttachments", (GLADapiproc) glad_vkCmdClearAttachments, 5, commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
    glad_vkCmdClearAttachments(commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
    _post_call_vulkan_callback(NULL, "vkCmdClearAttachments", (GLADapiproc) glad_vkCmdClearAttachments, 5, commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
    
}
PFN_vkCmdClearAttachments glad_debug_vkCmdClearAttachments = glad_debug_impl_vkCmdClearAttachments;
PFN_vkCmdClearColorImage glad_vkCmdClearColorImage = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue * pColor, uint32_t rangeCount, const VkImageSubresourceRange * pRanges) {
    _pre_call_vulkan_callback("vkCmdClearColorImage", (GLADapiproc) glad_vkCmdClearColorImage, 6, commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
    glad_vkCmdClearColorImage(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
    _post_call_vulkan_callback(NULL, "vkCmdClearColorImage", (GLADapiproc) glad_vkCmdClearColorImage, 6, commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
    
}
PFN_vkCmdClearColorImage glad_debug_vkCmdClearColorImage = glad_debug_impl_vkCmdClearColorImage;
PFN_vkCmdClearDepthStencilImage glad_vkCmdClearDepthStencilImage = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue * pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange * pRanges) {
    _pre_call_vulkan_callback("vkCmdClearDepthStencilImage", (GLADapiproc) glad_vkCmdClearDepthStencilImage, 6, commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
    glad_vkCmdClearDepthStencilImage(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
    _post_call_vulkan_callback(NULL, "vkCmdClearDepthStencilImage", (GLADapiproc) glad_vkCmdClearDepthStencilImage, 6, commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
    
}
PFN_vkCmdClearDepthStencilImage glad_debug_vkCmdClearDepthStencilImage = glad_debug_impl_vkCmdClearDepthStencilImage;
PFN_vkCmdCopyBuffer glad_vkCmdCopyBuffer = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy * pRegions) {
    _pre_call_vulkan_callback("vkCmdCopyBuffer", (GLADapiproc) glad_vkCmdCopyBuffer, 5, commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
    glad_vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
    _post_call_vulkan_callback(NULL, "vkCmdCopyBuffer", (GLADapiproc) glad_vkCmdCopyBuffer, 5, commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
    
}
PFN_vkCmdCopyBuffer glad_debug_vkCmdCopyBuffer = glad_debug_impl_vkCmdCopyBuffer;
PFN_vkCmdCopyBuffer2 glad_vkCmdCopyBuffer2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyBuffer2(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2 * pCopyBufferInfo) {
    _pre_call_vulkan_callback("vkCmdCopyBuffer2", (GLADapiproc) glad_vkCmdCopyBuffer2, 2, commandBuffer, pCopyBufferInfo);
    glad_vkCmdCopyBuffer2(commandBuffer, pCopyBufferInfo);
    _post_call_vulkan_callback(NULL, "vkCmdCopyBuffer2", (GLADapiproc) glad_vkCmdCopyBuffer2, 2, commandBuffer, pCopyBufferInfo);
    
}
PFN_vkCmdCopyBuffer2 glad_debug_vkCmdCopyBuffer2 = glad_debug_impl_vkCmdCopyBuffer2;
PFN_vkCmdCopyBuffer2KHR glad_vkCmdCopyBuffer2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2 * pCopyBufferInfo) {
    _pre_call_vulkan_callback("vkCmdCopyBuffer2KHR", (GLADapiproc) glad_vkCmdCopyBuffer2KHR, 2, commandBuffer, pCopyBufferInfo);
    glad_vkCmdCopyBuffer2KHR(commandBuffer, pCopyBufferInfo);
    _post_call_vulkan_callback(NULL, "vkCmdCopyBuffer2KHR", (GLADapiproc) glad_vkCmdCopyBuffer2KHR, 2, commandBuffer, pCopyBufferInfo);
    
}
PFN_vkCmdCopyBuffer2KHR glad_debug_vkCmdCopyBuffer2KHR = glad_debug_impl_vkCmdCopyBuffer2KHR;
PFN_vkCmdCopyBufferToImage glad_vkCmdCopyBufferToImage = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy * pRegions) {
    _pre_call_vulkan_callback("vkCmdCopyBufferToImage", (GLADapiproc) glad_vkCmdCopyBufferToImage, 6, commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
    glad_vkCmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
    _post_call_vulkan_callback(NULL, "vkCmdCopyBufferToImage", (GLADapiproc) glad_vkCmdCopyBufferToImage, 6, commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
    
}
PFN_vkCmdCopyBufferToImage glad_debug_vkCmdCopyBufferToImage = glad_debug_impl_vkCmdCopyBufferToImage;
PFN_vkCmdCopyBufferToImage2 glad_vkCmdCopyBufferToImage2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyBufferToImage2(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2 * pCopyBufferToImageInfo) {
    _pre_call_vulkan_callback("vkCmdCopyBufferToImage2", (GLADapiproc) glad_vkCmdCopyBufferToImage2, 2, commandBuffer, pCopyBufferToImageInfo);
    glad_vkCmdCopyBufferToImage2(commandBuffer, pCopyBufferToImageInfo);
    _post_call_vulkan_callback(NULL, "vkCmdCopyBufferToImage2", (GLADapiproc) glad_vkCmdCopyBufferToImage2, 2, commandBuffer, pCopyBufferToImageInfo);
    
}
PFN_vkCmdCopyBufferToImage2 glad_debug_vkCmdCopyBufferToImage2 = glad_debug_impl_vkCmdCopyBufferToImage2;
PFN_vkCmdCopyBufferToImage2KHR glad_vkCmdCopyBufferToImage2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyBufferToImage2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2 * pCopyBufferToImageInfo) {
    _pre_call_vulkan_callback("vkCmdCopyBufferToImage2KHR", (GLADapiproc) glad_vkCmdCopyBufferToImage2KHR, 2, commandBuffer, pCopyBufferToImageInfo);
    glad_vkCmdCopyBufferToImage2KHR(commandBuffer, pCopyBufferToImageInfo);
    _post_call_vulkan_callback(NULL, "vkCmdCopyBufferToImage2KHR", (GLADapiproc) glad_vkCmdCopyBufferToImage2KHR, 2, commandBuffer, pCopyBufferToImageInfo);
    
}
PFN_vkCmdCopyBufferToImage2KHR glad_debug_vkCmdCopyBufferToImage2KHR = glad_debug_impl_vkCmdCopyBufferToImage2KHR;
PFN_vkCmdCopyImage glad_vkCmdCopyImage = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy * pRegions) {
    _pre_call_vulkan_callback("vkCmdCopyImage", (GLADapiproc) glad_vkCmdCopyImage, 7, commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    glad_vkCmdCopyImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    _post_call_vulkan_callback(NULL, "vkCmdCopyImage", (GLADapiproc) glad_vkCmdCopyImage, 7, commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    
}
PFN_vkCmdCopyImage glad_debug_vkCmdCopyImage = glad_debug_impl_vkCmdCopyImage;
PFN_vkCmdCopyImage2 glad_vkCmdCopyImage2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyImage2(VkCommandBuffer commandBuffer, const VkCopyImageInfo2 * pCopyImageInfo) {
    _pre_call_vulkan_callback("vkCmdCopyImage2", (GLADapiproc) glad_vkCmdCopyImage2, 2, commandBuffer, pCopyImageInfo);
    glad_vkCmdCopyImage2(commandBuffer, pCopyImageInfo);
    _post_call_vulkan_callback(NULL, "vkCmdCopyImage2", (GLADapiproc) glad_vkCmdCopyImage2, 2, commandBuffer, pCopyImageInfo);
    
}
PFN_vkCmdCopyImage2 glad_debug_vkCmdCopyImage2 = glad_debug_impl_vkCmdCopyImage2;
PFN_vkCmdCopyImage2KHR glad_vkCmdCopyImage2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyImage2KHR(VkCommandBuffer commandBuffer, const VkCopyImageInfo2 * pCopyImageInfo) {
    _pre_call_vulkan_callback("vkCmdCopyImage2KHR", (GLADapiproc) glad_vkCmdCopyImage2KHR, 2, commandBuffer, pCopyImageInfo);
    glad_vkCmdCopyImage2KHR(commandBuffer, pCopyImageInfo);
    _post_call_vulkan_callback(NULL, "vkCmdCopyImage2KHR", (GLADapiproc) glad_vkCmdCopyImage2KHR, 2, commandBuffer, pCopyImageInfo);
    
}
PFN_vkCmdCopyImage2KHR glad_debug_vkCmdCopyImage2KHR = glad_debug_impl_vkCmdCopyImage2KHR;
PFN_vkCmdCopyImageToBuffer glad_vkCmdCopyImageToBuffer = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy * pRegions) {
    _pre_call_vulkan_callback("vkCmdCopyImageToBuffer", (GLADapiproc) glad_vkCmdCopyImageToBuffer, 6, commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
    glad_vkCmdCopyImageToBuffer(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
    _post_call_vulkan_callback(NULL, "vkCmdCopyImageToBuffer", (GLADapiproc) glad_vkCmdCopyImageToBuffer, 6, commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
    
}
PFN_vkCmdCopyImageToBuffer glad_debug_vkCmdCopyImageToBuffer = glad_debug_impl_vkCmdCopyImageToBuffer;
PFN_vkCmdCopyImageToBuffer2 glad_vkCmdCopyImageToBuffer2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyImageToBuffer2(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2 * pCopyImageToBufferInfo) {
    _pre_call_vulkan_callback("vkCmdCopyImageToBuffer2", (GLADapiproc) glad_vkCmdCopyImageToBuffer2, 2, commandBuffer, pCopyImageToBufferInfo);
    glad_vkCmdCopyImageToBuffer2(commandBuffer, pCopyImageToBufferInfo);
    _post_call_vulkan_callback(NULL, "vkCmdCopyImageToBuffer2", (GLADapiproc) glad_vkCmdCopyImageToBuffer2, 2, commandBuffer, pCopyImageToBufferInfo);
    
}
PFN_vkCmdCopyImageToBuffer2 glad_debug_vkCmdCopyImageToBuffer2 = glad_debug_impl_vkCmdCopyImageToBuffer2;
PFN_vkCmdCopyImageToBuffer2KHR glad_vkCmdCopyImageToBuffer2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyImageToBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2 * pCopyImageToBufferInfo) {
    _pre_call_vulkan_callback("vkCmdCopyImageToBuffer2KHR", (GLADapiproc) glad_vkCmdCopyImageToBuffer2KHR, 2, commandBuffer, pCopyImageToBufferInfo);
    glad_vkCmdCopyImageToBuffer2KHR(commandBuffer, pCopyImageToBufferInfo);
    _post_call_vulkan_callback(NULL, "vkCmdCopyImageToBuffer2KHR", (GLADapiproc) glad_vkCmdCopyImageToBuffer2KHR, 2, commandBuffer, pCopyImageToBufferInfo);
    
}
PFN_vkCmdCopyImageToBuffer2KHR glad_debug_vkCmdCopyImageToBuffer2KHR = glad_debug_impl_vkCmdCopyImageToBuffer2KHR;
PFN_vkCmdCopyQueryPoolResults glad_vkCmdCopyQueryPoolResults = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) {
    _pre_call_vulkan_callback("vkCmdCopyQueryPoolResults", (GLADapiproc) glad_vkCmdCopyQueryPoolResults, 8, commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
    glad_vkCmdCopyQueryPoolResults(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
    _post_call_vulkan_callback(NULL, "vkCmdCopyQueryPoolResults", (GLADapiproc) glad_vkCmdCopyQueryPoolResults, 8, commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
    
}
PFN_vkCmdCopyQueryPoolResults glad_debug_vkCmdCopyQueryPoolResults = glad_debug_impl_vkCmdCopyQueryPoolResults;
PFN_vkCmdDispatch glad_vkCmdDispatch = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
    _pre_call_vulkan_callback("vkCmdDispatch", (GLADapiproc) glad_vkCmdDispatch, 4, commandBuffer, groupCountX, groupCountY, groupCountZ);
    glad_vkCmdDispatch(commandBuffer, groupCountX, groupCountY, groupCountZ);
    _post_call_vulkan_callback(NULL, "vkCmdDispatch", (GLADapiproc) glad_vkCmdDispatch, 4, commandBuffer, groupCountX, groupCountY, groupCountZ);
    
}
PFN_vkCmdDispatch glad_debug_vkCmdDispatch = glad_debug_impl_vkCmdDispatch;
PFN_vkCmdDispatchBase glad_vkCmdDispatchBase = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
    _pre_call_vulkan_callback("vkCmdDispatchBase", (GLADapiproc) glad_vkCmdDispatchBase, 7, commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    glad_vkCmdDispatchBase(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    _post_call_vulkan_callback(NULL, "vkCmdDispatchBase", (GLADapiproc) glad_vkCmdDispatchBase, 7, commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    
}
PFN_vkCmdDispatchBase glad_debug_vkCmdDispatchBase = glad_debug_impl_vkCmdDispatchBase;
PFN_vkCmdDispatchBaseKHR glad_vkCmdDispatchBaseKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
    _pre_call_vulkan_callback("vkCmdDispatchBaseKHR", (GLADapiproc) glad_vkCmdDispatchBaseKHR, 7, commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    glad_vkCmdDispatchBaseKHR(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    _post_call_vulkan_callback(NULL, "vkCmdDispatchBaseKHR", (GLADapiproc) glad_vkCmdDispatchBaseKHR, 7, commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    
}
PFN_vkCmdDispatchBaseKHR glad_debug_vkCmdDispatchBaseKHR = glad_debug_impl_vkCmdDispatchBaseKHR;
PFN_vkCmdDispatchIndirect glad_vkCmdDispatchIndirect = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) {
    _pre_call_vulkan_callback("vkCmdDispatchIndirect", (GLADapiproc) glad_vkCmdDispatchIndirect, 3, commandBuffer, buffer, offset);
    glad_vkCmdDispatchIndirect(commandBuffer, buffer, offset);
    _post_call_vulkan_callback(NULL, "vkCmdDispatchIndirect", (GLADapiproc) glad_vkCmdDispatchIndirect, 3, commandBuffer, buffer, offset);
    
}
PFN_vkCmdDispatchIndirect glad_debug_vkCmdDispatchIndirect = glad_debug_impl_vkCmdDispatchIndirect;
PFN_vkCmdDraw glad_vkCmdDraw = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
    _pre_call_vulkan_callback("vkCmdDraw", (GLADapiproc) glad_vkCmdDraw, 5, commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
    glad_vkCmdDraw(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
    _post_call_vulkan_callback(NULL, "vkCmdDraw", (GLADapiproc) glad_vkCmdDraw, 5, commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
    
}
PFN_vkCmdDraw glad_debug_vkCmdDraw = glad_debug_impl_vkCmdDraw;
PFN_vkCmdDrawIndexed glad_vkCmdDrawIndexed = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) {
    _pre_call_vulkan_callback("vkCmdDrawIndexed", (GLADapiproc) glad_vkCmdDrawIndexed, 6, commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
    glad_vkCmdDrawIndexed(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
    _post_call_vulkan_callback(NULL, "vkCmdDrawIndexed", (GLADapiproc) glad_vkCmdDrawIndexed, 6, commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
    
}
PFN_vkCmdDrawIndexed glad_debug_vkCmdDrawIndexed = glad_debug_impl_vkCmdDrawIndexed;
PFN_vkCmdDrawIndexedIndirect glad_vkCmdDrawIndexedIndirect = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) {
    _pre_call_vulkan_callback("vkCmdDrawIndexedIndirect", (GLADapiproc) glad_vkCmdDrawIndexedIndirect, 5, commandBuffer, buffer, offset, drawCount, stride);
    glad_vkCmdDrawIndexedIndirect(commandBuffer, buffer, offset, drawCount, stride);
    _post_call_vulkan_callback(NULL, "vkCmdDrawIndexedIndirect", (GLADapiproc) glad_vkCmdDrawIndexedIndirect, 5, commandBuffer, buffer, offset, drawCount, stride);
    
}
PFN_vkCmdDrawIndexedIndirect glad_debug_vkCmdDrawIndexedIndirect = glad_debug_impl_vkCmdDrawIndexedIndirect;
PFN_vkCmdDrawIndexedIndirectCount glad_vkCmdDrawIndexedIndirectCount = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
    _pre_call_vulkan_callback("vkCmdDrawIndexedIndirectCount", (GLADapiproc) glad_vkCmdDrawIndexedIndirectCount, 7, commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    glad_vkCmdDrawIndexedIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    _post_call_vulkan_callback(NULL, "vkCmdDrawIndexedIndirectCount", (GLADapiproc) glad_vkCmdDrawIndexedIndirectCount, 7, commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    
}
PFN_vkCmdDrawIndexedIndirectCount glad_debug_vkCmdDrawIndexedIndirectCount = glad_debug_impl_vkCmdDrawIndexedIndirectCount;
PFN_vkCmdDrawIndexedIndirectCountAMD glad_vkCmdDrawIndexedIndirectCountAMD = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
    _pre_call_vulkan_callback("vkCmdDrawIndexedIndirectCountAMD", (GLADapiproc) glad_vkCmdDrawIndexedIndirectCountAMD, 7, commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    glad_vkCmdDrawIndexedIndirectCountAMD(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    _post_call_vulkan_callback(NULL, "vkCmdDrawIndexedIndirectCountAMD", (GLADapiproc) glad_vkCmdDrawIndexedIndirectCountAMD, 7, commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    
}
PFN_vkCmdDrawIndexedIndirectCountAMD glad_debug_vkCmdDrawIndexedIndirectCountAMD = glad_debug_impl_vkCmdDrawIndexedIndirectCountAMD;
PFN_vkCmdDrawIndexedIndirectCountKHR glad_vkCmdDrawIndexedIndirectCountKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdDrawIndexedIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
    _pre_call_vulkan_callback("vkCmdDrawIndexedIndirectCountKHR", (GLADapiproc) glad_vkCmdDrawIndexedIndirectCountKHR, 7, commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    glad_vkCmdDrawIndexedIndirectCountKHR(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    _post_call_vulkan_callback(NULL, "vkCmdDrawIndexedIndirectCountKHR", (GLADapiproc) glad_vkCmdDrawIndexedIndirectCountKHR, 7, commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    
}
PFN_vkCmdDrawIndexedIndirectCountKHR glad_debug_vkCmdDrawIndexedIndirectCountKHR = glad_debug_impl_vkCmdDrawIndexedIndirectCountKHR;
PFN_vkCmdDrawIndirect glad_vkCmdDrawIndirect = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) {
    _pre_call_vulkan_callback("vkCmdDrawIndirect", (GLADapiproc) glad_vkCmdDrawIndirect, 5, commandBuffer, buffer, offset, drawCount, stride);
    glad_vkCmdDrawIndirect(commandBuffer, buffer, offset, drawCount, stride);
    _post_call_vulkan_callback(NULL, "vkCmdDrawIndirect", (GLADapiproc) glad_vkCmdDrawIndirect, 5, commandBuffer, buffer, offset, drawCount, stride);
    
}
PFN_vkCmdDrawIndirect glad_debug_vkCmdDrawIndirect = glad_debug_impl_vkCmdDrawIndirect;
PFN_vkCmdDrawIndirectCount glad_vkCmdDrawIndirectCount = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
    _pre_call_vulkan_callback("vkCmdDrawIndirectCount", (GLADapiproc) glad_vkCmdDrawIndirectCount, 7, commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    glad_vkCmdDrawIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    _post_call_vulkan_callback(NULL, "vkCmdDrawIndirectCount", (GLADapiproc) glad_vkCmdDrawIndirectCount, 7, commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    
}
PFN_vkCmdDrawIndirectCount glad_debug_vkCmdDrawIndirectCount = glad_debug_impl_vkCmdDrawIndirectCount;
PFN_vkCmdDrawIndirectCountAMD glad_vkCmdDrawIndirectCountAMD = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
    _pre_call_vulkan_callback("vkCmdDrawIndirectCountAMD", (GLADapiproc) glad_vkCmdDrawIndirectCountAMD, 7, commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    glad_vkCmdDrawIndirectCountAMD(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    _post_call_vulkan_callback(NULL, "vkCmdDrawIndirectCountAMD", (GLADapiproc) glad_vkCmdDrawIndirectCountAMD, 7, commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    
}
PFN_vkCmdDrawIndirectCountAMD glad_debug_vkCmdDrawIndirectCountAMD = glad_debug_impl_vkCmdDrawIndirectCountAMD;
PFN_vkCmdDrawIndirectCountKHR glad_vkCmdDrawIndirectCountKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdDrawIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
    _pre_call_vulkan_callback("vkCmdDrawIndirectCountKHR", (GLADapiproc) glad_vkCmdDrawIndirectCountKHR, 7, commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    glad_vkCmdDrawIndirectCountKHR(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    _post_call_vulkan_callback(NULL, "vkCmdDrawIndirectCountKHR", (GLADapiproc) glad_vkCmdDrawIndirectCountKHR, 7, commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    
}
PFN_vkCmdDrawIndirectCountKHR glad_debug_vkCmdDrawIndirectCountKHR = glad_debug_impl_vkCmdDrawIndirectCountKHR;
PFN_vkCmdEndQuery glad_vkCmdEndQuery = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) {
    _pre_call_vulkan_callback("vkCmdEndQuery", (GLADapiproc) glad_vkCmdEndQuery, 3, commandBuffer, queryPool, query);
    glad_vkCmdEndQuery(commandBuffer, queryPool, query);
    _post_call_vulkan_callback(NULL, "vkCmdEndQuery", (GLADapiproc) glad_vkCmdEndQuery, 3, commandBuffer, queryPool, query);
    
}
PFN_vkCmdEndQuery glad_debug_vkCmdEndQuery = glad_debug_impl_vkCmdEndQuery;
PFN_vkCmdEndRenderPass glad_vkCmdEndRenderPass = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdEndRenderPass(VkCommandBuffer commandBuffer) {
    _pre_call_vulkan_callback("vkCmdEndRenderPass", (GLADapiproc) glad_vkCmdEndRenderPass, 1, commandBuffer);
    glad_vkCmdEndRenderPass(commandBuffer);
    _post_call_vulkan_callback(NULL, "vkCmdEndRenderPass", (GLADapiproc) glad_vkCmdEndRenderPass, 1, commandBuffer);
    
}
PFN_vkCmdEndRenderPass glad_debug_vkCmdEndRenderPass = glad_debug_impl_vkCmdEndRenderPass;
PFN_vkCmdEndRenderPass2 glad_vkCmdEndRenderPass2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfo * pSubpassEndInfo) {
    _pre_call_vulkan_callback("vkCmdEndRenderPass2", (GLADapiproc) glad_vkCmdEndRenderPass2, 2, commandBuffer, pSubpassEndInfo);
    glad_vkCmdEndRenderPass2(commandBuffer, pSubpassEndInfo);
    _post_call_vulkan_callback(NULL, "vkCmdEndRenderPass2", (GLADapiproc) glad_vkCmdEndRenderPass2, 2, commandBuffer, pSubpassEndInfo);
    
}
PFN_vkCmdEndRenderPass2 glad_debug_vkCmdEndRenderPass2 = glad_debug_impl_vkCmdEndRenderPass2;
PFN_vkCmdEndRenderPass2KHR glad_vkCmdEndRenderPass2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdEndRenderPass2KHR(VkCommandBuffer commandBuffer, const VkSubpassEndInfo * pSubpassEndInfo) {
    _pre_call_vulkan_callback("vkCmdEndRenderPass2KHR", (GLADapiproc) glad_vkCmdEndRenderPass2KHR, 2, commandBuffer, pSubpassEndInfo);
    glad_vkCmdEndRenderPass2KHR(commandBuffer, pSubpassEndInfo);
    _post_call_vulkan_callback(NULL, "vkCmdEndRenderPass2KHR", (GLADapiproc) glad_vkCmdEndRenderPass2KHR, 2, commandBuffer, pSubpassEndInfo);
    
}
PFN_vkCmdEndRenderPass2KHR glad_debug_vkCmdEndRenderPass2KHR = glad_debug_impl_vkCmdEndRenderPass2KHR;
PFN_vkCmdEndRendering glad_vkCmdEndRendering = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdEndRendering(VkCommandBuffer commandBuffer) {
    _pre_call_vulkan_callback("vkCmdEndRendering", (GLADapiproc) glad_vkCmdEndRendering, 1, commandBuffer);
    glad_vkCmdEndRendering(commandBuffer);
    _post_call_vulkan_callback(NULL, "vkCmdEndRendering", (GLADapiproc) glad_vkCmdEndRendering, 1, commandBuffer);
    
}
PFN_vkCmdEndRendering glad_debug_vkCmdEndRendering = glad_debug_impl_vkCmdEndRendering;
PFN_vkCmdEndRenderingKHR glad_vkCmdEndRenderingKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdEndRenderingKHR(VkCommandBuffer commandBuffer) {
    _pre_call_vulkan_callback("vkCmdEndRenderingKHR", (GLADapiproc) glad_vkCmdEndRenderingKHR, 1, commandBuffer);
    glad_vkCmdEndRenderingKHR(commandBuffer);
    _post_call_vulkan_callback(NULL, "vkCmdEndRenderingKHR", (GLADapiproc) glad_vkCmdEndRenderingKHR, 1, commandBuffer);
    
}
PFN_vkCmdEndRenderingKHR glad_debug_vkCmdEndRenderingKHR = glad_debug_impl_vkCmdEndRenderingKHR;
PFN_vkCmdExecuteCommands glad_vkCmdExecuteCommands = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer * pCommandBuffers) {
    _pre_call_vulkan_callback("vkCmdExecuteCommands", (GLADapiproc) glad_vkCmdExecuteCommands, 3, commandBuffer, commandBufferCount, pCommandBuffers);
    glad_vkCmdExecuteCommands(commandBuffer, commandBufferCount, pCommandBuffers);
    _post_call_vulkan_callback(NULL, "vkCmdExecuteCommands", (GLADapiproc) glad_vkCmdExecuteCommands, 3, commandBuffer, commandBufferCount, pCommandBuffers);
    
}
PFN_vkCmdExecuteCommands glad_debug_vkCmdExecuteCommands = glad_debug_impl_vkCmdExecuteCommands;
PFN_vkCmdFillBuffer glad_vkCmdFillBuffer = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) {
    _pre_call_vulkan_callback("vkCmdFillBuffer", (GLADapiproc) glad_vkCmdFillBuffer, 5, commandBuffer, dstBuffer, dstOffset, size, data);
    glad_vkCmdFillBuffer(commandBuffer, dstBuffer, dstOffset, size, data);
    _post_call_vulkan_callback(NULL, "vkCmdFillBuffer", (GLADapiproc) glad_vkCmdFillBuffer, 5, commandBuffer, dstBuffer, dstOffset, size, data);
    
}
PFN_vkCmdFillBuffer glad_debug_vkCmdFillBuffer = glad_debug_impl_vkCmdFillBuffer;
PFN_vkCmdNextSubpass glad_vkCmdNextSubpass = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) {
    _pre_call_vulkan_callback("vkCmdNextSubpass", (GLADapiproc) glad_vkCmdNextSubpass, 2, commandBuffer, contents);
    glad_vkCmdNextSubpass(commandBuffer, contents);
    _post_call_vulkan_callback(NULL, "vkCmdNextSubpass", (GLADapiproc) glad_vkCmdNextSubpass, 2, commandBuffer, contents);
    
}
PFN_vkCmdNextSubpass glad_debug_vkCmdNextSubpass = glad_debug_impl_vkCmdNextSubpass;
PFN_vkCmdNextSubpass2 glad_vkCmdNextSubpass2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo * pSubpassBeginInfo, const VkSubpassEndInfo * pSubpassEndInfo) {
    _pre_call_vulkan_callback("vkCmdNextSubpass2", (GLADapiproc) glad_vkCmdNextSubpass2, 3, commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
    glad_vkCmdNextSubpass2(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
    _post_call_vulkan_callback(NULL, "vkCmdNextSubpass2", (GLADapiproc) glad_vkCmdNextSubpass2, 3, commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
    
}
PFN_vkCmdNextSubpass2 glad_debug_vkCmdNextSubpass2 = glad_debug_impl_vkCmdNextSubpass2;
PFN_vkCmdNextSubpass2KHR glad_vkCmdNextSubpass2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdNextSubpass2KHR(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo * pSubpassBeginInfo, const VkSubpassEndInfo * pSubpassEndInfo) {
    _pre_call_vulkan_callback("vkCmdNextSubpass2KHR", (GLADapiproc) glad_vkCmdNextSubpass2KHR, 3, commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
    glad_vkCmdNextSubpass2KHR(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
    _post_call_vulkan_callback(NULL, "vkCmdNextSubpass2KHR", (GLADapiproc) glad_vkCmdNextSubpass2KHR, 3, commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
    
}
PFN_vkCmdNextSubpass2KHR glad_debug_vkCmdNextSubpass2KHR = glad_debug_impl_vkCmdNextSubpass2KHR;
PFN_vkCmdPipelineBarrier glad_vkCmdPipelineBarrier = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier * pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier * pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier * pImageMemoryBarriers) {
    _pre_call_vulkan_callback("vkCmdPipelineBarrier", (GLADapiproc) glad_vkCmdPipelineBarrier, 10, commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    glad_vkCmdPipelineBarrier(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    _post_call_vulkan_callback(NULL, "vkCmdPipelineBarrier", (GLADapiproc) glad_vkCmdPipelineBarrier, 10, commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    
}
PFN_vkCmdPipelineBarrier glad_debug_vkCmdPipelineBarrier = glad_debug_impl_vkCmdPipelineBarrier;
PFN_vkCmdPipelineBarrier2 glad_vkCmdPipelineBarrier2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdPipelineBarrier2(VkCommandBuffer commandBuffer, const VkDependencyInfo * pDependencyInfo) {
    _pre_call_vulkan_callback("vkCmdPipelineBarrier2", (GLADapiproc) glad_vkCmdPipelineBarrier2, 2, commandBuffer, pDependencyInfo);
    glad_vkCmdPipelineBarrier2(commandBuffer, pDependencyInfo);
    _post_call_vulkan_callback(NULL, "vkCmdPipelineBarrier2", (GLADapiproc) glad_vkCmdPipelineBarrier2, 2, commandBuffer, pDependencyInfo);
    
}
PFN_vkCmdPipelineBarrier2 glad_debug_vkCmdPipelineBarrier2 = glad_debug_impl_vkCmdPipelineBarrier2;
PFN_vkCmdPipelineBarrier2KHR glad_vkCmdPipelineBarrier2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdPipelineBarrier2KHR(VkCommandBuffer commandBuffer, const VkDependencyInfo * pDependencyInfo) {
    _pre_call_vulkan_callback("vkCmdPipelineBarrier2KHR", (GLADapiproc) glad_vkCmdPipelineBarrier2KHR, 2, commandBuffer, pDependencyInfo);
    glad_vkCmdPipelineBarrier2KHR(commandBuffer, pDependencyInfo);
    _post_call_vulkan_callback(NULL, "vkCmdPipelineBarrier2KHR", (GLADapiproc) glad_vkCmdPipelineBarrier2KHR, 2, commandBuffer, pDependencyInfo);
    
}
PFN_vkCmdPipelineBarrier2KHR glad_debug_vkCmdPipelineBarrier2KHR = glad_debug_impl_vkCmdPipelineBarrier2KHR;
PFN_vkCmdPushConstants glad_vkCmdPushConstants = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void * pValues) {
    _pre_call_vulkan_callback("vkCmdPushConstants", (GLADapiproc) glad_vkCmdPushConstants, 6, commandBuffer, layout, stageFlags, offset, size, pValues);
    glad_vkCmdPushConstants(commandBuffer, layout, stageFlags, offset, size, pValues);
    _post_call_vulkan_callback(NULL, "vkCmdPushConstants", (GLADapiproc) glad_vkCmdPushConstants, 6, commandBuffer, layout, stageFlags, offset, size, pValues);
    
}
PFN_vkCmdPushConstants glad_debug_vkCmdPushConstants = glad_debug_impl_vkCmdPushConstants;
PFN_vkCmdPushConstants2 glad_vkCmdPushConstants2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdPushConstants2(VkCommandBuffer commandBuffer, const VkPushConstantsInfo * pPushConstantsInfo) {
    _pre_call_vulkan_callback("vkCmdPushConstants2", (GLADapiproc) glad_vkCmdPushConstants2, 2, commandBuffer, pPushConstantsInfo);
    glad_vkCmdPushConstants2(commandBuffer, pPushConstantsInfo);
    _post_call_vulkan_callback(NULL, "vkCmdPushConstants2", (GLADapiproc) glad_vkCmdPushConstants2, 2, commandBuffer, pPushConstantsInfo);
    
}
PFN_vkCmdPushConstants2 glad_debug_vkCmdPushConstants2 = glad_debug_impl_vkCmdPushConstants2;
PFN_vkCmdPushConstants2KHR glad_vkCmdPushConstants2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdPushConstants2KHR(VkCommandBuffer commandBuffer, const VkPushConstantsInfo * pPushConstantsInfo) {
    _pre_call_vulkan_callback("vkCmdPushConstants2KHR", (GLADapiproc) glad_vkCmdPushConstants2KHR, 2, commandBuffer, pPushConstantsInfo);
    glad_vkCmdPushConstants2KHR(commandBuffer, pPushConstantsInfo);
    _post_call_vulkan_callback(NULL, "vkCmdPushConstants2KHR", (GLADapiproc) glad_vkCmdPushConstants2KHR, 2, commandBuffer, pPushConstantsInfo);
    
}
PFN_vkCmdPushConstants2KHR glad_debug_vkCmdPushConstants2KHR = glad_debug_impl_vkCmdPushConstants2KHR;
PFN_vkCmdPushDescriptorSet glad_vkCmdPushDescriptorSet = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdPushDescriptorSet(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet * pDescriptorWrites) {
    _pre_call_vulkan_callback("vkCmdPushDescriptorSet", (GLADapiproc) glad_vkCmdPushDescriptorSet, 6, commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
    glad_vkCmdPushDescriptorSet(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
    _post_call_vulkan_callback(NULL, "vkCmdPushDescriptorSet", (GLADapiproc) glad_vkCmdPushDescriptorSet, 6, commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
    
}
PFN_vkCmdPushDescriptorSet glad_debug_vkCmdPushDescriptorSet = glad_debug_impl_vkCmdPushDescriptorSet;
PFN_vkCmdPushDescriptorSet2 glad_vkCmdPushDescriptorSet2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdPushDescriptorSet2(VkCommandBuffer commandBuffer, const VkPushDescriptorSetInfo * pPushDescriptorSetInfo) {
    _pre_call_vulkan_callback("vkCmdPushDescriptorSet2", (GLADapiproc) glad_vkCmdPushDescriptorSet2, 2, commandBuffer, pPushDescriptorSetInfo);
    glad_vkCmdPushDescriptorSet2(commandBuffer, pPushDescriptorSetInfo);
    _post_call_vulkan_callback(NULL, "vkCmdPushDescriptorSet2", (GLADapiproc) glad_vkCmdPushDescriptorSet2, 2, commandBuffer, pPushDescriptorSetInfo);
    
}
PFN_vkCmdPushDescriptorSet2 glad_debug_vkCmdPushDescriptorSet2 = glad_debug_impl_vkCmdPushDescriptorSet2;
PFN_vkCmdPushDescriptorSet2KHR glad_vkCmdPushDescriptorSet2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdPushDescriptorSet2KHR(VkCommandBuffer commandBuffer, const VkPushDescriptorSetInfo * pPushDescriptorSetInfo) {
    _pre_call_vulkan_callback("vkCmdPushDescriptorSet2KHR", (GLADapiproc) glad_vkCmdPushDescriptorSet2KHR, 2, commandBuffer, pPushDescriptorSetInfo);
    glad_vkCmdPushDescriptorSet2KHR(commandBuffer, pPushDescriptorSetInfo);
    _post_call_vulkan_callback(NULL, "vkCmdPushDescriptorSet2KHR", (GLADapiproc) glad_vkCmdPushDescriptorSet2KHR, 2, commandBuffer, pPushDescriptorSetInfo);
    
}
PFN_vkCmdPushDescriptorSet2KHR glad_debug_vkCmdPushDescriptorSet2KHR = glad_debug_impl_vkCmdPushDescriptorSet2KHR;
PFN_vkCmdPushDescriptorSetKHR glad_vkCmdPushDescriptorSetKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet * pDescriptorWrites) {
    _pre_call_vulkan_callback("vkCmdPushDescriptorSetKHR", (GLADapiproc) glad_vkCmdPushDescriptorSetKHR, 6, commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
    glad_vkCmdPushDescriptorSetKHR(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
    _post_call_vulkan_callback(NULL, "vkCmdPushDescriptorSetKHR", (GLADapiproc) glad_vkCmdPushDescriptorSetKHR, 6, commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
    
}
PFN_vkCmdPushDescriptorSetKHR glad_debug_vkCmdPushDescriptorSetKHR = glad_debug_impl_vkCmdPushDescriptorSetKHR;
PFN_vkCmdPushDescriptorSetWithTemplate glad_vkCmdPushDescriptorSetWithTemplate = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdPushDescriptorSetWithTemplate(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void * pData) {
    _pre_call_vulkan_callback("vkCmdPushDescriptorSetWithTemplate", (GLADapiproc) glad_vkCmdPushDescriptorSetWithTemplate, 5, commandBuffer, descriptorUpdateTemplate, layout, set, pData);
    glad_vkCmdPushDescriptorSetWithTemplate(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
    _post_call_vulkan_callback(NULL, "vkCmdPushDescriptorSetWithTemplate", (GLADapiproc) glad_vkCmdPushDescriptorSetWithTemplate, 5, commandBuffer, descriptorUpdateTemplate, layout, set, pData);
    
}
PFN_vkCmdPushDescriptorSetWithTemplate glad_debug_vkCmdPushDescriptorSetWithTemplate = glad_debug_impl_vkCmdPushDescriptorSetWithTemplate;
PFN_vkCmdPushDescriptorSetWithTemplate2 glad_vkCmdPushDescriptorSetWithTemplate2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdPushDescriptorSetWithTemplate2(VkCommandBuffer commandBuffer, const VkPushDescriptorSetWithTemplateInfo * pPushDescriptorSetWithTemplateInfo) {
    _pre_call_vulkan_callback("vkCmdPushDescriptorSetWithTemplate2", (GLADapiproc) glad_vkCmdPushDescriptorSetWithTemplate2, 2, commandBuffer, pPushDescriptorSetWithTemplateInfo);
    glad_vkCmdPushDescriptorSetWithTemplate2(commandBuffer, pPushDescriptorSetWithTemplateInfo);
    _post_call_vulkan_callback(NULL, "vkCmdPushDescriptorSetWithTemplate2", (GLADapiproc) glad_vkCmdPushDescriptorSetWithTemplate2, 2, commandBuffer, pPushDescriptorSetWithTemplateInfo);
    
}
PFN_vkCmdPushDescriptorSetWithTemplate2 glad_debug_vkCmdPushDescriptorSetWithTemplate2 = glad_debug_impl_vkCmdPushDescriptorSetWithTemplate2;
PFN_vkCmdPushDescriptorSetWithTemplate2KHR glad_vkCmdPushDescriptorSetWithTemplate2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdPushDescriptorSetWithTemplate2KHR(VkCommandBuffer commandBuffer, const VkPushDescriptorSetWithTemplateInfo * pPushDescriptorSetWithTemplateInfo) {
    _pre_call_vulkan_callback("vkCmdPushDescriptorSetWithTemplate2KHR", (GLADapiproc) glad_vkCmdPushDescriptorSetWithTemplate2KHR, 2, commandBuffer, pPushDescriptorSetWithTemplateInfo);
    glad_vkCmdPushDescriptorSetWithTemplate2KHR(commandBuffer, pPushDescriptorSetWithTemplateInfo);
    _post_call_vulkan_callback(NULL, "vkCmdPushDescriptorSetWithTemplate2KHR", (GLADapiproc) glad_vkCmdPushDescriptorSetWithTemplate2KHR, 2, commandBuffer, pPushDescriptorSetWithTemplateInfo);
    
}
PFN_vkCmdPushDescriptorSetWithTemplate2KHR glad_debug_vkCmdPushDescriptorSetWithTemplate2KHR = glad_debug_impl_vkCmdPushDescriptorSetWithTemplate2KHR;
PFN_vkCmdPushDescriptorSetWithTemplateKHR glad_vkCmdPushDescriptorSetWithTemplateKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void * pData) {
    _pre_call_vulkan_callback("vkCmdPushDescriptorSetWithTemplateKHR", (GLADapiproc) glad_vkCmdPushDescriptorSetWithTemplateKHR, 5, commandBuffer, descriptorUpdateTemplate, layout, set, pData);
    glad_vkCmdPushDescriptorSetWithTemplateKHR(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
    _post_call_vulkan_callback(NULL, "vkCmdPushDescriptorSetWithTemplateKHR", (GLADapiproc) glad_vkCmdPushDescriptorSetWithTemplateKHR, 5, commandBuffer, descriptorUpdateTemplate, layout, set, pData);
    
}
PFN_vkCmdPushDescriptorSetWithTemplateKHR glad_debug_vkCmdPushDescriptorSetWithTemplateKHR = glad_debug_impl_vkCmdPushDescriptorSetWithTemplateKHR;
PFN_vkCmdResetEvent glad_vkCmdResetEvent = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) {
    _pre_call_vulkan_callback("vkCmdResetEvent", (GLADapiproc) glad_vkCmdResetEvent, 3, commandBuffer, event, stageMask);
    glad_vkCmdResetEvent(commandBuffer, event, stageMask);
    _post_call_vulkan_callback(NULL, "vkCmdResetEvent", (GLADapiproc) glad_vkCmdResetEvent, 3, commandBuffer, event, stageMask);
    
}
PFN_vkCmdResetEvent glad_debug_vkCmdResetEvent = glad_debug_impl_vkCmdResetEvent;
PFN_vkCmdResetEvent2 glad_vkCmdResetEvent2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdResetEvent2(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags2 stageMask) {
    _pre_call_vulkan_callback("vkCmdResetEvent2", (GLADapiproc) glad_vkCmdResetEvent2, 3, commandBuffer, event, stageMask);
    glad_vkCmdResetEvent2(commandBuffer, event, stageMask);
    _post_call_vulkan_callback(NULL, "vkCmdResetEvent2", (GLADapiproc) glad_vkCmdResetEvent2, 3, commandBuffer, event, stageMask);
    
}
PFN_vkCmdResetEvent2 glad_debug_vkCmdResetEvent2 = glad_debug_impl_vkCmdResetEvent2;
PFN_vkCmdResetEvent2KHR glad_vkCmdResetEvent2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdResetEvent2KHR(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags2 stageMask) {
    _pre_call_vulkan_callback("vkCmdResetEvent2KHR", (GLADapiproc) glad_vkCmdResetEvent2KHR, 3, commandBuffer, event, stageMask);
    glad_vkCmdResetEvent2KHR(commandBuffer, event, stageMask);
    _post_call_vulkan_callback(NULL, "vkCmdResetEvent2KHR", (GLADapiproc) glad_vkCmdResetEvent2KHR, 3, commandBuffer, event, stageMask);
    
}
PFN_vkCmdResetEvent2KHR glad_debug_vkCmdResetEvent2KHR = glad_debug_impl_vkCmdResetEvent2KHR;
PFN_vkCmdResetQueryPool glad_vkCmdResetQueryPool = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) {
    _pre_call_vulkan_callback("vkCmdResetQueryPool", (GLADapiproc) glad_vkCmdResetQueryPool, 4, commandBuffer, queryPool, firstQuery, queryCount);
    glad_vkCmdResetQueryPool(commandBuffer, queryPool, firstQuery, queryCount);
    _post_call_vulkan_callback(NULL, "vkCmdResetQueryPool", (GLADapiproc) glad_vkCmdResetQueryPool, 4, commandBuffer, queryPool, firstQuery, queryCount);
    
}
PFN_vkCmdResetQueryPool glad_debug_vkCmdResetQueryPool = glad_debug_impl_vkCmdResetQueryPool;
PFN_vkCmdResolveImage glad_vkCmdResolveImage = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve * pRegions) {
    _pre_call_vulkan_callback("vkCmdResolveImage", (GLADapiproc) glad_vkCmdResolveImage, 7, commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    glad_vkCmdResolveImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    _post_call_vulkan_callback(NULL, "vkCmdResolveImage", (GLADapiproc) glad_vkCmdResolveImage, 7, commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    
}
PFN_vkCmdResolveImage glad_debug_vkCmdResolveImage = glad_debug_impl_vkCmdResolveImage;
PFN_vkCmdResolveImage2 glad_vkCmdResolveImage2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdResolveImage2(VkCommandBuffer commandBuffer, const VkResolveImageInfo2 * pResolveImageInfo) {
    _pre_call_vulkan_callback("vkCmdResolveImage2", (GLADapiproc) glad_vkCmdResolveImage2, 2, commandBuffer, pResolveImageInfo);
    glad_vkCmdResolveImage2(commandBuffer, pResolveImageInfo);
    _post_call_vulkan_callback(NULL, "vkCmdResolveImage2", (GLADapiproc) glad_vkCmdResolveImage2, 2, commandBuffer, pResolveImageInfo);
    
}
PFN_vkCmdResolveImage2 glad_debug_vkCmdResolveImage2 = glad_debug_impl_vkCmdResolveImage2;
PFN_vkCmdResolveImage2KHR glad_vkCmdResolveImage2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdResolveImage2KHR(VkCommandBuffer commandBuffer, const VkResolveImageInfo2 * pResolveImageInfo) {
    _pre_call_vulkan_callback("vkCmdResolveImage2KHR", (GLADapiproc) glad_vkCmdResolveImage2KHR, 2, commandBuffer, pResolveImageInfo);
    glad_vkCmdResolveImage2KHR(commandBuffer, pResolveImageInfo);
    _post_call_vulkan_callback(NULL, "vkCmdResolveImage2KHR", (GLADapiproc) glad_vkCmdResolveImage2KHR, 2, commandBuffer, pResolveImageInfo);
    
}
PFN_vkCmdResolveImage2KHR glad_debug_vkCmdResolveImage2KHR = glad_debug_impl_vkCmdResolveImage2KHR;
PFN_vkCmdSetAlphaToCoverageEnableEXT glad_vkCmdSetAlphaToCoverageEnableEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetAlphaToCoverageEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToCoverageEnable) {
    _pre_call_vulkan_callback("vkCmdSetAlphaToCoverageEnableEXT", (GLADapiproc) glad_vkCmdSetAlphaToCoverageEnableEXT, 2, commandBuffer, alphaToCoverageEnable);
    glad_vkCmdSetAlphaToCoverageEnableEXT(commandBuffer, alphaToCoverageEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetAlphaToCoverageEnableEXT", (GLADapiproc) glad_vkCmdSetAlphaToCoverageEnableEXT, 2, commandBuffer, alphaToCoverageEnable);
    
}
PFN_vkCmdSetAlphaToCoverageEnableEXT glad_debug_vkCmdSetAlphaToCoverageEnableEXT = glad_debug_impl_vkCmdSetAlphaToCoverageEnableEXT;
PFN_vkCmdSetAlphaToOneEnableEXT glad_vkCmdSetAlphaToOneEnableEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetAlphaToOneEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToOneEnable) {
    _pre_call_vulkan_callback("vkCmdSetAlphaToOneEnableEXT", (GLADapiproc) glad_vkCmdSetAlphaToOneEnableEXT, 2, commandBuffer, alphaToOneEnable);
    glad_vkCmdSetAlphaToOneEnableEXT(commandBuffer, alphaToOneEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetAlphaToOneEnableEXT", (GLADapiproc) glad_vkCmdSetAlphaToOneEnableEXT, 2, commandBuffer, alphaToOneEnable);
    
}
PFN_vkCmdSetAlphaToOneEnableEXT glad_debug_vkCmdSetAlphaToOneEnableEXT = glad_debug_impl_vkCmdSetAlphaToOneEnableEXT;
PFN_vkCmdSetBlendConstants glad_vkCmdSetBlendConstants = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants [4]) {
    _pre_call_vulkan_callback("vkCmdSetBlendConstants", (GLADapiproc) glad_vkCmdSetBlendConstants, 2, commandBuffer, blendConstants);
    glad_vkCmdSetBlendConstants(commandBuffer, blendConstants);
    _post_call_vulkan_callback(NULL, "vkCmdSetBlendConstants", (GLADapiproc) glad_vkCmdSetBlendConstants, 2, commandBuffer, blendConstants);
    
}
PFN_vkCmdSetBlendConstants glad_debug_vkCmdSetBlendConstants = glad_debug_impl_vkCmdSetBlendConstants;
PFN_vkCmdSetColorBlendAdvancedEXT glad_vkCmdSetColorBlendAdvancedEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetColorBlendAdvancedEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendAdvancedEXT * pColorBlendAdvanced) {
    _pre_call_vulkan_callback("vkCmdSetColorBlendAdvancedEXT", (GLADapiproc) glad_vkCmdSetColorBlendAdvancedEXT, 4, commandBuffer, firstAttachment, attachmentCount, pColorBlendAdvanced);
    glad_vkCmdSetColorBlendAdvancedEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendAdvanced);
    _post_call_vulkan_callback(NULL, "vkCmdSetColorBlendAdvancedEXT", (GLADapiproc) glad_vkCmdSetColorBlendAdvancedEXT, 4, commandBuffer, firstAttachment, attachmentCount, pColorBlendAdvanced);
    
}
PFN_vkCmdSetColorBlendAdvancedEXT glad_debug_vkCmdSetColorBlendAdvancedEXT = glad_debug_impl_vkCmdSetColorBlendAdvancedEXT;
PFN_vkCmdSetColorBlendEnableEXT glad_vkCmdSetColorBlendEnableEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetColorBlendEnableEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkBool32 * pColorBlendEnables) {
    _pre_call_vulkan_callback("vkCmdSetColorBlendEnableEXT", (GLADapiproc) glad_vkCmdSetColorBlendEnableEXT, 4, commandBuffer, firstAttachment, attachmentCount, pColorBlendEnables);
    glad_vkCmdSetColorBlendEnableEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendEnables);
    _post_call_vulkan_callback(NULL, "vkCmdSetColorBlendEnableEXT", (GLADapiproc) glad_vkCmdSetColorBlendEnableEXT, 4, commandBuffer, firstAttachment, attachmentCount, pColorBlendEnables);
    
}
PFN_vkCmdSetColorBlendEnableEXT glad_debug_vkCmdSetColorBlendEnableEXT = glad_debug_impl_vkCmdSetColorBlendEnableEXT;
PFN_vkCmdSetColorBlendEquationEXT glad_vkCmdSetColorBlendEquationEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetColorBlendEquationEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendEquationEXT * pColorBlendEquations) {
    _pre_call_vulkan_callback("vkCmdSetColorBlendEquationEXT", (GLADapiproc) glad_vkCmdSetColorBlendEquationEXT, 4, commandBuffer, firstAttachment, attachmentCount, pColorBlendEquations);
    glad_vkCmdSetColorBlendEquationEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendEquations);
    _post_call_vulkan_callback(NULL, "vkCmdSetColorBlendEquationEXT", (GLADapiproc) glad_vkCmdSetColorBlendEquationEXT, 4, commandBuffer, firstAttachment, attachmentCount, pColorBlendEquations);
    
}
PFN_vkCmdSetColorBlendEquationEXT glad_debug_vkCmdSetColorBlendEquationEXT = glad_debug_impl_vkCmdSetColorBlendEquationEXT;
PFN_vkCmdSetColorWriteMaskEXT glad_vkCmdSetColorWriteMaskEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetColorWriteMaskEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorComponentFlags * pColorWriteMasks) {
    _pre_call_vulkan_callback("vkCmdSetColorWriteMaskEXT", (GLADapiproc) glad_vkCmdSetColorWriteMaskEXT, 4, commandBuffer, firstAttachment, attachmentCount, pColorWriteMasks);
    glad_vkCmdSetColorWriteMaskEXT(commandBuffer, firstAttachment, attachmentCount, pColorWriteMasks);
    _post_call_vulkan_callback(NULL, "vkCmdSetColorWriteMaskEXT", (GLADapiproc) glad_vkCmdSetColorWriteMaskEXT, 4, commandBuffer, firstAttachment, attachmentCount, pColorWriteMasks);
    
}
PFN_vkCmdSetColorWriteMaskEXT glad_debug_vkCmdSetColorWriteMaskEXT = glad_debug_impl_vkCmdSetColorWriteMaskEXT;
PFN_vkCmdSetConservativeRasterizationModeEXT glad_vkCmdSetConservativeRasterizationModeEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetConservativeRasterizationModeEXT(VkCommandBuffer commandBuffer, VkConservativeRasterizationModeEXT conservativeRasterizationMode) {
    _pre_call_vulkan_callback("vkCmdSetConservativeRasterizationModeEXT", (GLADapiproc) glad_vkCmdSetConservativeRasterizationModeEXT, 2, commandBuffer, conservativeRasterizationMode);
    glad_vkCmdSetConservativeRasterizationModeEXT(commandBuffer, conservativeRasterizationMode);
    _post_call_vulkan_callback(NULL, "vkCmdSetConservativeRasterizationModeEXT", (GLADapiproc) glad_vkCmdSetConservativeRasterizationModeEXT, 2, commandBuffer, conservativeRasterizationMode);
    
}
PFN_vkCmdSetConservativeRasterizationModeEXT glad_debug_vkCmdSetConservativeRasterizationModeEXT = glad_debug_impl_vkCmdSetConservativeRasterizationModeEXT;
PFN_vkCmdSetCoverageModulationModeNV glad_vkCmdSetCoverageModulationModeNV = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetCoverageModulationModeNV(VkCommandBuffer commandBuffer, VkCoverageModulationModeNV coverageModulationMode) {
    _pre_call_vulkan_callback("vkCmdSetCoverageModulationModeNV", (GLADapiproc) glad_vkCmdSetCoverageModulationModeNV, 2, commandBuffer, coverageModulationMode);
    glad_vkCmdSetCoverageModulationModeNV(commandBuffer, coverageModulationMode);
    _post_call_vulkan_callback(NULL, "vkCmdSetCoverageModulationModeNV", (GLADapiproc) glad_vkCmdSetCoverageModulationModeNV, 2, commandBuffer, coverageModulationMode);
    
}
PFN_vkCmdSetCoverageModulationModeNV glad_debug_vkCmdSetCoverageModulationModeNV = glad_debug_impl_vkCmdSetCoverageModulationModeNV;
PFN_vkCmdSetCoverageModulationTableEnableNV glad_vkCmdSetCoverageModulationTableEnableNV = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetCoverageModulationTableEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageModulationTableEnable) {
    _pre_call_vulkan_callback("vkCmdSetCoverageModulationTableEnableNV", (GLADapiproc) glad_vkCmdSetCoverageModulationTableEnableNV, 2, commandBuffer, coverageModulationTableEnable);
    glad_vkCmdSetCoverageModulationTableEnableNV(commandBuffer, coverageModulationTableEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetCoverageModulationTableEnableNV", (GLADapiproc) glad_vkCmdSetCoverageModulationTableEnableNV, 2, commandBuffer, coverageModulationTableEnable);
    
}
PFN_vkCmdSetCoverageModulationTableEnableNV glad_debug_vkCmdSetCoverageModulationTableEnableNV = glad_debug_impl_vkCmdSetCoverageModulationTableEnableNV;
PFN_vkCmdSetCoverageModulationTableNV glad_vkCmdSetCoverageModulationTableNV = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetCoverageModulationTableNV(VkCommandBuffer commandBuffer, uint32_t coverageModulationTableCount, const float * pCoverageModulationTable) {
    _pre_call_vulkan_callback("vkCmdSetCoverageModulationTableNV", (GLADapiproc) glad_vkCmdSetCoverageModulationTableNV, 3, commandBuffer, coverageModulationTableCount, pCoverageModulationTable);
    glad_vkCmdSetCoverageModulationTableNV(commandBuffer, coverageModulationTableCount, pCoverageModulationTable);
    _post_call_vulkan_callback(NULL, "vkCmdSetCoverageModulationTableNV", (GLADapiproc) glad_vkCmdSetCoverageModulationTableNV, 3, commandBuffer, coverageModulationTableCount, pCoverageModulationTable);
    
}
PFN_vkCmdSetCoverageModulationTableNV glad_debug_vkCmdSetCoverageModulationTableNV = glad_debug_impl_vkCmdSetCoverageModulationTableNV;
PFN_vkCmdSetCoverageReductionModeNV glad_vkCmdSetCoverageReductionModeNV = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetCoverageReductionModeNV(VkCommandBuffer commandBuffer, VkCoverageReductionModeNV coverageReductionMode) {
    _pre_call_vulkan_callback("vkCmdSetCoverageReductionModeNV", (GLADapiproc) glad_vkCmdSetCoverageReductionModeNV, 2, commandBuffer, coverageReductionMode);
    glad_vkCmdSetCoverageReductionModeNV(commandBuffer, coverageReductionMode);
    _post_call_vulkan_callback(NULL, "vkCmdSetCoverageReductionModeNV", (GLADapiproc) glad_vkCmdSetCoverageReductionModeNV, 2, commandBuffer, coverageReductionMode);
    
}
PFN_vkCmdSetCoverageReductionModeNV glad_debug_vkCmdSetCoverageReductionModeNV = glad_debug_impl_vkCmdSetCoverageReductionModeNV;
PFN_vkCmdSetCoverageToColorEnableNV glad_vkCmdSetCoverageToColorEnableNV = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetCoverageToColorEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageToColorEnable) {
    _pre_call_vulkan_callback("vkCmdSetCoverageToColorEnableNV", (GLADapiproc) glad_vkCmdSetCoverageToColorEnableNV, 2, commandBuffer, coverageToColorEnable);
    glad_vkCmdSetCoverageToColorEnableNV(commandBuffer, coverageToColorEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetCoverageToColorEnableNV", (GLADapiproc) glad_vkCmdSetCoverageToColorEnableNV, 2, commandBuffer, coverageToColorEnable);
    
}
PFN_vkCmdSetCoverageToColorEnableNV glad_debug_vkCmdSetCoverageToColorEnableNV = glad_debug_impl_vkCmdSetCoverageToColorEnableNV;
PFN_vkCmdSetCoverageToColorLocationNV glad_vkCmdSetCoverageToColorLocationNV = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetCoverageToColorLocationNV(VkCommandBuffer commandBuffer, uint32_t coverageToColorLocation) {
    _pre_call_vulkan_callback("vkCmdSetCoverageToColorLocationNV", (GLADapiproc) glad_vkCmdSetCoverageToColorLocationNV, 2, commandBuffer, coverageToColorLocation);
    glad_vkCmdSetCoverageToColorLocationNV(commandBuffer, coverageToColorLocation);
    _post_call_vulkan_callback(NULL, "vkCmdSetCoverageToColorLocationNV", (GLADapiproc) glad_vkCmdSetCoverageToColorLocationNV, 2, commandBuffer, coverageToColorLocation);
    
}
PFN_vkCmdSetCoverageToColorLocationNV glad_debug_vkCmdSetCoverageToColorLocationNV = glad_debug_impl_vkCmdSetCoverageToColorLocationNV;
PFN_vkCmdSetCullMode glad_vkCmdSetCullMode = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetCullMode(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) {
    _pre_call_vulkan_callback("vkCmdSetCullMode", (GLADapiproc) glad_vkCmdSetCullMode, 2, commandBuffer, cullMode);
    glad_vkCmdSetCullMode(commandBuffer, cullMode);
    _post_call_vulkan_callback(NULL, "vkCmdSetCullMode", (GLADapiproc) glad_vkCmdSetCullMode, 2, commandBuffer, cullMode);
    
}
PFN_vkCmdSetCullMode glad_debug_vkCmdSetCullMode = glad_debug_impl_vkCmdSetCullMode;
PFN_vkCmdSetCullModeEXT glad_vkCmdSetCullModeEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetCullModeEXT(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) {
    _pre_call_vulkan_callback("vkCmdSetCullModeEXT", (GLADapiproc) glad_vkCmdSetCullModeEXT, 2, commandBuffer, cullMode);
    glad_vkCmdSetCullModeEXT(commandBuffer, cullMode);
    _post_call_vulkan_callback(NULL, "vkCmdSetCullModeEXT", (GLADapiproc) glad_vkCmdSetCullModeEXT, 2, commandBuffer, cullMode);
    
}
PFN_vkCmdSetCullModeEXT glad_debug_vkCmdSetCullModeEXT = glad_debug_impl_vkCmdSetCullModeEXT;
PFN_vkCmdSetDepthBias glad_vkCmdSetDepthBias = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) {
    _pre_call_vulkan_callback("vkCmdSetDepthBias", (GLADapiproc) glad_vkCmdSetDepthBias, 4, commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
    glad_vkCmdSetDepthBias(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthBias", (GLADapiproc) glad_vkCmdSetDepthBias, 4, commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
    
}
PFN_vkCmdSetDepthBias glad_debug_vkCmdSetDepthBias = glad_debug_impl_vkCmdSetDepthBias;
PFN_vkCmdSetDepthBiasEnable glad_vkCmdSetDepthBiasEnable = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthBiasEnable(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) {
    _pre_call_vulkan_callback("vkCmdSetDepthBiasEnable", (GLADapiproc) glad_vkCmdSetDepthBiasEnable, 2, commandBuffer, depthBiasEnable);
    glad_vkCmdSetDepthBiasEnable(commandBuffer, depthBiasEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthBiasEnable", (GLADapiproc) glad_vkCmdSetDepthBiasEnable, 2, commandBuffer, depthBiasEnable);
    
}
PFN_vkCmdSetDepthBiasEnable glad_debug_vkCmdSetDepthBiasEnable = glad_debug_impl_vkCmdSetDepthBiasEnable;
PFN_vkCmdSetDepthBiasEnableEXT glad_vkCmdSetDepthBiasEnableEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthBiasEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) {
    _pre_call_vulkan_callback("vkCmdSetDepthBiasEnableEXT", (GLADapiproc) glad_vkCmdSetDepthBiasEnableEXT, 2, commandBuffer, depthBiasEnable);
    glad_vkCmdSetDepthBiasEnableEXT(commandBuffer, depthBiasEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthBiasEnableEXT", (GLADapiproc) glad_vkCmdSetDepthBiasEnableEXT, 2, commandBuffer, depthBiasEnable);
    
}
PFN_vkCmdSetDepthBiasEnableEXT glad_debug_vkCmdSetDepthBiasEnableEXT = glad_debug_impl_vkCmdSetDepthBiasEnableEXT;
PFN_vkCmdSetDepthBounds glad_vkCmdSetDepthBounds = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) {
    _pre_call_vulkan_callback("vkCmdSetDepthBounds", (GLADapiproc) glad_vkCmdSetDepthBounds, 3, commandBuffer, minDepthBounds, maxDepthBounds);
    glad_vkCmdSetDepthBounds(commandBuffer, minDepthBounds, maxDepthBounds);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthBounds", (GLADapiproc) glad_vkCmdSetDepthBounds, 3, commandBuffer, minDepthBounds, maxDepthBounds);
    
}
PFN_vkCmdSetDepthBounds glad_debug_vkCmdSetDepthBounds = glad_debug_impl_vkCmdSetDepthBounds;
PFN_vkCmdSetDepthBoundsTestEnable glad_vkCmdSetDepthBoundsTestEnable = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthBoundsTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) {
    _pre_call_vulkan_callback("vkCmdSetDepthBoundsTestEnable", (GLADapiproc) glad_vkCmdSetDepthBoundsTestEnable, 2, commandBuffer, depthBoundsTestEnable);
    glad_vkCmdSetDepthBoundsTestEnable(commandBuffer, depthBoundsTestEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthBoundsTestEnable", (GLADapiproc) glad_vkCmdSetDepthBoundsTestEnable, 2, commandBuffer, depthBoundsTestEnable);
    
}
PFN_vkCmdSetDepthBoundsTestEnable glad_debug_vkCmdSetDepthBoundsTestEnable = glad_debug_impl_vkCmdSetDepthBoundsTestEnable;
PFN_vkCmdSetDepthBoundsTestEnableEXT glad_vkCmdSetDepthBoundsTestEnableEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthBoundsTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) {
    _pre_call_vulkan_callback("vkCmdSetDepthBoundsTestEnableEXT", (GLADapiproc) glad_vkCmdSetDepthBoundsTestEnableEXT, 2, commandBuffer, depthBoundsTestEnable);
    glad_vkCmdSetDepthBoundsTestEnableEXT(commandBuffer, depthBoundsTestEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthBoundsTestEnableEXT", (GLADapiproc) glad_vkCmdSetDepthBoundsTestEnableEXT, 2, commandBuffer, depthBoundsTestEnable);
    
}
PFN_vkCmdSetDepthBoundsTestEnableEXT glad_debug_vkCmdSetDepthBoundsTestEnableEXT = glad_debug_impl_vkCmdSetDepthBoundsTestEnableEXT;
PFN_vkCmdSetDepthClampEnableEXT glad_vkCmdSetDepthClampEnableEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthClampEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClampEnable) {
    _pre_call_vulkan_callback("vkCmdSetDepthClampEnableEXT", (GLADapiproc) glad_vkCmdSetDepthClampEnableEXT, 2, commandBuffer, depthClampEnable);
    glad_vkCmdSetDepthClampEnableEXT(commandBuffer, depthClampEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthClampEnableEXT", (GLADapiproc) glad_vkCmdSetDepthClampEnableEXT, 2, commandBuffer, depthClampEnable);
    
}
PFN_vkCmdSetDepthClampEnableEXT glad_debug_vkCmdSetDepthClampEnableEXT = glad_debug_impl_vkCmdSetDepthClampEnableEXT;
PFN_vkCmdSetDepthClampRangeEXT glad_vkCmdSetDepthClampRangeEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthClampRangeEXT(VkCommandBuffer commandBuffer, VkDepthClampModeEXT depthClampMode, const VkDepthClampRangeEXT * pDepthClampRange) {
    _pre_call_vulkan_callback("vkCmdSetDepthClampRangeEXT", (GLADapiproc) glad_vkCmdSetDepthClampRangeEXT, 3, commandBuffer, depthClampMode, pDepthClampRange);
    glad_vkCmdSetDepthClampRangeEXT(commandBuffer, depthClampMode, pDepthClampRange);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthClampRangeEXT", (GLADapiproc) glad_vkCmdSetDepthClampRangeEXT, 3, commandBuffer, depthClampMode, pDepthClampRange);
    
}
PFN_vkCmdSetDepthClampRangeEXT glad_debug_vkCmdSetDepthClampRangeEXT = glad_debug_impl_vkCmdSetDepthClampRangeEXT;
PFN_vkCmdSetDepthClipEnableEXT glad_vkCmdSetDepthClipEnableEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthClipEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClipEnable) {
    _pre_call_vulkan_callback("vkCmdSetDepthClipEnableEXT", (GLADapiproc) glad_vkCmdSetDepthClipEnableEXT, 2, commandBuffer, depthClipEnable);
    glad_vkCmdSetDepthClipEnableEXT(commandBuffer, depthClipEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthClipEnableEXT", (GLADapiproc) glad_vkCmdSetDepthClipEnableEXT, 2, commandBuffer, depthClipEnable);
    
}
PFN_vkCmdSetDepthClipEnableEXT glad_debug_vkCmdSetDepthClipEnableEXT = glad_debug_impl_vkCmdSetDepthClipEnableEXT;
PFN_vkCmdSetDepthClipNegativeOneToOneEXT glad_vkCmdSetDepthClipNegativeOneToOneEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthClipNegativeOneToOneEXT(VkCommandBuffer commandBuffer, VkBool32 negativeOneToOne) {
    _pre_call_vulkan_callback("vkCmdSetDepthClipNegativeOneToOneEXT", (GLADapiproc) glad_vkCmdSetDepthClipNegativeOneToOneEXT, 2, commandBuffer, negativeOneToOne);
    glad_vkCmdSetDepthClipNegativeOneToOneEXT(commandBuffer, negativeOneToOne);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthClipNegativeOneToOneEXT", (GLADapiproc) glad_vkCmdSetDepthClipNegativeOneToOneEXT, 2, commandBuffer, negativeOneToOne);
    
}
PFN_vkCmdSetDepthClipNegativeOneToOneEXT glad_debug_vkCmdSetDepthClipNegativeOneToOneEXT = glad_debug_impl_vkCmdSetDepthClipNegativeOneToOneEXT;
PFN_vkCmdSetDepthCompareOp glad_vkCmdSetDepthCompareOp = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthCompareOp(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) {
    _pre_call_vulkan_callback("vkCmdSetDepthCompareOp", (GLADapiproc) glad_vkCmdSetDepthCompareOp, 2, commandBuffer, depthCompareOp);
    glad_vkCmdSetDepthCompareOp(commandBuffer, depthCompareOp);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthCompareOp", (GLADapiproc) glad_vkCmdSetDepthCompareOp, 2, commandBuffer, depthCompareOp);
    
}
PFN_vkCmdSetDepthCompareOp glad_debug_vkCmdSetDepthCompareOp = glad_debug_impl_vkCmdSetDepthCompareOp;
PFN_vkCmdSetDepthCompareOpEXT glad_vkCmdSetDepthCompareOpEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthCompareOpEXT(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) {
    _pre_call_vulkan_callback("vkCmdSetDepthCompareOpEXT", (GLADapiproc) glad_vkCmdSetDepthCompareOpEXT, 2, commandBuffer, depthCompareOp);
    glad_vkCmdSetDepthCompareOpEXT(commandBuffer, depthCompareOp);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthCompareOpEXT", (GLADapiproc) glad_vkCmdSetDepthCompareOpEXT, 2, commandBuffer, depthCompareOp);
    
}
PFN_vkCmdSetDepthCompareOpEXT glad_debug_vkCmdSetDepthCompareOpEXT = glad_debug_impl_vkCmdSetDepthCompareOpEXT;
PFN_vkCmdSetDepthTestEnable glad_vkCmdSetDepthTestEnable = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) {
    _pre_call_vulkan_callback("vkCmdSetDepthTestEnable", (GLADapiproc) glad_vkCmdSetDepthTestEnable, 2, commandBuffer, depthTestEnable);
    glad_vkCmdSetDepthTestEnable(commandBuffer, depthTestEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthTestEnable", (GLADapiproc) glad_vkCmdSetDepthTestEnable, 2, commandBuffer, depthTestEnable);
    
}
PFN_vkCmdSetDepthTestEnable glad_debug_vkCmdSetDepthTestEnable = glad_debug_impl_vkCmdSetDepthTestEnable;
PFN_vkCmdSetDepthTestEnableEXT glad_vkCmdSetDepthTestEnableEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) {
    _pre_call_vulkan_callback("vkCmdSetDepthTestEnableEXT", (GLADapiproc) glad_vkCmdSetDepthTestEnableEXT, 2, commandBuffer, depthTestEnable);
    glad_vkCmdSetDepthTestEnableEXT(commandBuffer, depthTestEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthTestEnableEXT", (GLADapiproc) glad_vkCmdSetDepthTestEnableEXT, 2, commandBuffer, depthTestEnable);
    
}
PFN_vkCmdSetDepthTestEnableEXT glad_debug_vkCmdSetDepthTestEnableEXT = glad_debug_impl_vkCmdSetDepthTestEnableEXT;
PFN_vkCmdSetDepthWriteEnable glad_vkCmdSetDepthWriteEnable = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthWriteEnable(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) {
    _pre_call_vulkan_callback("vkCmdSetDepthWriteEnable", (GLADapiproc) glad_vkCmdSetDepthWriteEnable, 2, commandBuffer, depthWriteEnable);
    glad_vkCmdSetDepthWriteEnable(commandBuffer, depthWriteEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthWriteEnable", (GLADapiproc) glad_vkCmdSetDepthWriteEnable, 2, commandBuffer, depthWriteEnable);
    
}
PFN_vkCmdSetDepthWriteEnable glad_debug_vkCmdSetDepthWriteEnable = glad_debug_impl_vkCmdSetDepthWriteEnable;
PFN_vkCmdSetDepthWriteEnableEXT glad_vkCmdSetDepthWriteEnableEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDepthWriteEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) {
    _pre_call_vulkan_callback("vkCmdSetDepthWriteEnableEXT", (GLADapiproc) glad_vkCmdSetDepthWriteEnableEXT, 2, commandBuffer, depthWriteEnable);
    glad_vkCmdSetDepthWriteEnableEXT(commandBuffer, depthWriteEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetDepthWriteEnableEXT", (GLADapiproc) glad_vkCmdSetDepthWriteEnableEXT, 2, commandBuffer, depthWriteEnable);
    
}
PFN_vkCmdSetDepthWriteEnableEXT glad_debug_vkCmdSetDepthWriteEnableEXT = glad_debug_impl_vkCmdSetDepthWriteEnableEXT;
PFN_vkCmdSetDescriptorBufferOffsets2EXT glad_vkCmdSetDescriptorBufferOffsets2EXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDescriptorBufferOffsets2EXT(VkCommandBuffer commandBuffer, const VkSetDescriptorBufferOffsetsInfoEXT * pSetDescriptorBufferOffsetsInfo) {
    _pre_call_vulkan_callback("vkCmdSetDescriptorBufferOffsets2EXT", (GLADapiproc) glad_vkCmdSetDescriptorBufferOffsets2EXT, 2, commandBuffer, pSetDescriptorBufferOffsetsInfo);
    glad_vkCmdSetDescriptorBufferOffsets2EXT(commandBuffer, pSetDescriptorBufferOffsetsInfo);
    _post_call_vulkan_callback(NULL, "vkCmdSetDescriptorBufferOffsets2EXT", (GLADapiproc) glad_vkCmdSetDescriptorBufferOffsets2EXT, 2, commandBuffer, pSetDescriptorBufferOffsetsInfo);
    
}
PFN_vkCmdSetDescriptorBufferOffsets2EXT glad_debug_vkCmdSetDescriptorBufferOffsets2EXT = glad_debug_impl_vkCmdSetDescriptorBufferOffsets2EXT;
PFN_vkCmdSetDeviceMask glad_vkCmdSetDeviceMask = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) {
    _pre_call_vulkan_callback("vkCmdSetDeviceMask", (GLADapiproc) glad_vkCmdSetDeviceMask, 2, commandBuffer, deviceMask);
    glad_vkCmdSetDeviceMask(commandBuffer, deviceMask);
    _post_call_vulkan_callback(NULL, "vkCmdSetDeviceMask", (GLADapiproc) glad_vkCmdSetDeviceMask, 2, commandBuffer, deviceMask);
    
}
PFN_vkCmdSetDeviceMask glad_debug_vkCmdSetDeviceMask = glad_debug_impl_vkCmdSetDeviceMask;
PFN_vkCmdSetDeviceMaskKHR glad_vkCmdSetDeviceMaskKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) {
    _pre_call_vulkan_callback("vkCmdSetDeviceMaskKHR", (GLADapiproc) glad_vkCmdSetDeviceMaskKHR, 2, commandBuffer, deviceMask);
    glad_vkCmdSetDeviceMaskKHR(commandBuffer, deviceMask);
    _post_call_vulkan_callback(NULL, "vkCmdSetDeviceMaskKHR", (GLADapiproc) glad_vkCmdSetDeviceMaskKHR, 2, commandBuffer, deviceMask);
    
}
PFN_vkCmdSetDeviceMaskKHR glad_debug_vkCmdSetDeviceMaskKHR = glad_debug_impl_vkCmdSetDeviceMaskKHR;
PFN_vkCmdSetEvent glad_vkCmdSetEvent = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) {
    _pre_call_vulkan_callback("vkCmdSetEvent", (GLADapiproc) glad_vkCmdSetEvent, 3, commandBuffer, event, stageMask);
    glad_vkCmdSetEvent(commandBuffer, event, stageMask);
    _post_call_vulkan_callback(NULL, "vkCmdSetEvent", (GLADapiproc) glad_vkCmdSetEvent, 3, commandBuffer, event, stageMask);
    
}
PFN_vkCmdSetEvent glad_debug_vkCmdSetEvent = glad_debug_impl_vkCmdSetEvent;
PFN_vkCmdSetEvent2 glad_vkCmdSetEvent2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetEvent2(VkCommandBuffer commandBuffer, VkEvent event, const VkDependencyInfo * pDependencyInfo) {
    _pre_call_vulkan_callback("vkCmdSetEvent2", (GLADapiproc) glad_vkCmdSetEvent2, 3, commandBuffer, event, pDependencyInfo);
    glad_vkCmdSetEvent2(commandBuffer, event, pDependencyInfo);
    _post_call_vulkan_callback(NULL, "vkCmdSetEvent2", (GLADapiproc) glad_vkCmdSetEvent2, 3, commandBuffer, event, pDependencyInfo);
    
}
PFN_vkCmdSetEvent2 glad_debug_vkCmdSetEvent2 = glad_debug_impl_vkCmdSetEvent2;
PFN_vkCmdSetEvent2KHR glad_vkCmdSetEvent2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetEvent2KHR(VkCommandBuffer commandBuffer, VkEvent event, const VkDependencyInfo * pDependencyInfo) {
    _pre_call_vulkan_callback("vkCmdSetEvent2KHR", (GLADapiproc) glad_vkCmdSetEvent2KHR, 3, commandBuffer, event, pDependencyInfo);
    glad_vkCmdSetEvent2KHR(commandBuffer, event, pDependencyInfo);
    _post_call_vulkan_callback(NULL, "vkCmdSetEvent2KHR", (GLADapiproc) glad_vkCmdSetEvent2KHR, 3, commandBuffer, event, pDependencyInfo);
    
}
PFN_vkCmdSetEvent2KHR glad_debug_vkCmdSetEvent2KHR = glad_debug_impl_vkCmdSetEvent2KHR;
PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT glad_vkCmdSetExtraPrimitiveOverestimationSizeEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetExtraPrimitiveOverestimationSizeEXT(VkCommandBuffer commandBuffer, float extraPrimitiveOverestimationSize) {
    _pre_call_vulkan_callback("vkCmdSetExtraPrimitiveOverestimationSizeEXT", (GLADapiproc) glad_vkCmdSetExtraPrimitiveOverestimationSizeEXT, 2, commandBuffer, extraPrimitiveOverestimationSize);
    glad_vkCmdSetExtraPrimitiveOverestimationSizeEXT(commandBuffer, extraPrimitiveOverestimationSize);
    _post_call_vulkan_callback(NULL, "vkCmdSetExtraPrimitiveOverestimationSizeEXT", (GLADapiproc) glad_vkCmdSetExtraPrimitiveOverestimationSizeEXT, 2, commandBuffer, extraPrimitiveOverestimationSize);
    
}
PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT glad_debug_vkCmdSetExtraPrimitiveOverestimationSizeEXT = glad_debug_impl_vkCmdSetExtraPrimitiveOverestimationSizeEXT;
PFN_vkCmdSetFrontFace glad_vkCmdSetFrontFace = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetFrontFace(VkCommandBuffer commandBuffer, VkFrontFace frontFace) {
    _pre_call_vulkan_callback("vkCmdSetFrontFace", (GLADapiproc) glad_vkCmdSetFrontFace, 2, commandBuffer, frontFace);
    glad_vkCmdSetFrontFace(commandBuffer, frontFace);
    _post_call_vulkan_callback(NULL, "vkCmdSetFrontFace", (GLADapiproc) glad_vkCmdSetFrontFace, 2, commandBuffer, frontFace);
    
}
PFN_vkCmdSetFrontFace glad_debug_vkCmdSetFrontFace = glad_debug_impl_vkCmdSetFrontFace;
PFN_vkCmdSetFrontFaceEXT glad_vkCmdSetFrontFaceEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetFrontFaceEXT(VkCommandBuffer commandBuffer, VkFrontFace frontFace) {
    _pre_call_vulkan_callback("vkCmdSetFrontFaceEXT", (GLADapiproc) glad_vkCmdSetFrontFaceEXT, 2, commandBuffer, frontFace);
    glad_vkCmdSetFrontFaceEXT(commandBuffer, frontFace);
    _post_call_vulkan_callback(NULL, "vkCmdSetFrontFaceEXT", (GLADapiproc) glad_vkCmdSetFrontFaceEXT, 2, commandBuffer, frontFace);
    
}
PFN_vkCmdSetFrontFaceEXT glad_debug_vkCmdSetFrontFaceEXT = glad_debug_impl_vkCmdSetFrontFaceEXT;
PFN_vkCmdSetLineRasterizationModeEXT glad_vkCmdSetLineRasterizationModeEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetLineRasterizationModeEXT(VkCommandBuffer commandBuffer, VkLineRasterizationModeEXT lineRasterizationMode) {
    _pre_call_vulkan_callback("vkCmdSetLineRasterizationModeEXT", (GLADapiproc) glad_vkCmdSetLineRasterizationModeEXT, 2, commandBuffer, lineRasterizationMode);
    glad_vkCmdSetLineRasterizationModeEXT(commandBuffer, lineRasterizationMode);
    _post_call_vulkan_callback(NULL, "vkCmdSetLineRasterizationModeEXT", (GLADapiproc) glad_vkCmdSetLineRasterizationModeEXT, 2, commandBuffer, lineRasterizationMode);
    
}
PFN_vkCmdSetLineRasterizationModeEXT glad_debug_vkCmdSetLineRasterizationModeEXT = glad_debug_impl_vkCmdSetLineRasterizationModeEXT;
PFN_vkCmdSetLineStipple glad_vkCmdSetLineStipple = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetLineStipple(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) {
    _pre_call_vulkan_callback("vkCmdSetLineStipple", (GLADapiproc) glad_vkCmdSetLineStipple, 3, commandBuffer, lineStippleFactor, lineStipplePattern);
    glad_vkCmdSetLineStipple(commandBuffer, lineStippleFactor, lineStipplePattern);
    _post_call_vulkan_callback(NULL, "vkCmdSetLineStipple", (GLADapiproc) glad_vkCmdSetLineStipple, 3, commandBuffer, lineStippleFactor, lineStipplePattern);
    
}
PFN_vkCmdSetLineStipple glad_debug_vkCmdSetLineStipple = glad_debug_impl_vkCmdSetLineStipple;
PFN_vkCmdSetLineStippleEXT glad_vkCmdSetLineStippleEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetLineStippleEXT(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) {
    _pre_call_vulkan_callback("vkCmdSetLineStippleEXT", (GLADapiproc) glad_vkCmdSetLineStippleEXT, 3, commandBuffer, lineStippleFactor, lineStipplePattern);
    glad_vkCmdSetLineStippleEXT(commandBuffer, lineStippleFactor, lineStipplePattern);
    _post_call_vulkan_callback(NULL, "vkCmdSetLineStippleEXT", (GLADapiproc) glad_vkCmdSetLineStippleEXT, 3, commandBuffer, lineStippleFactor, lineStipplePattern);
    
}
PFN_vkCmdSetLineStippleEXT glad_debug_vkCmdSetLineStippleEXT = glad_debug_impl_vkCmdSetLineStippleEXT;
PFN_vkCmdSetLineStippleEnableEXT glad_vkCmdSetLineStippleEnableEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetLineStippleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stippledLineEnable) {
    _pre_call_vulkan_callback("vkCmdSetLineStippleEnableEXT", (GLADapiproc) glad_vkCmdSetLineStippleEnableEXT, 2, commandBuffer, stippledLineEnable);
    glad_vkCmdSetLineStippleEnableEXT(commandBuffer, stippledLineEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetLineStippleEnableEXT", (GLADapiproc) glad_vkCmdSetLineStippleEnableEXT, 2, commandBuffer, stippledLineEnable);
    
}
PFN_vkCmdSetLineStippleEnableEXT glad_debug_vkCmdSetLineStippleEnableEXT = glad_debug_impl_vkCmdSetLineStippleEnableEXT;
PFN_vkCmdSetLineStippleKHR glad_vkCmdSetLineStippleKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetLineStippleKHR(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) {
    _pre_call_vulkan_callback("vkCmdSetLineStippleKHR", (GLADapiproc) glad_vkCmdSetLineStippleKHR, 3, commandBuffer, lineStippleFactor, lineStipplePattern);
    glad_vkCmdSetLineStippleKHR(commandBuffer, lineStippleFactor, lineStipplePattern);
    _post_call_vulkan_callback(NULL, "vkCmdSetLineStippleKHR", (GLADapiproc) glad_vkCmdSetLineStippleKHR, 3, commandBuffer, lineStippleFactor, lineStipplePattern);
    
}
PFN_vkCmdSetLineStippleKHR glad_debug_vkCmdSetLineStippleKHR = glad_debug_impl_vkCmdSetLineStippleKHR;
PFN_vkCmdSetLineWidth glad_vkCmdSetLineWidth = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) {
    _pre_call_vulkan_callback("vkCmdSetLineWidth", (GLADapiproc) glad_vkCmdSetLineWidth, 2, commandBuffer, lineWidth);
    glad_vkCmdSetLineWidth(commandBuffer, lineWidth);
    _post_call_vulkan_callback(NULL, "vkCmdSetLineWidth", (GLADapiproc) glad_vkCmdSetLineWidth, 2, commandBuffer, lineWidth);
    
}
PFN_vkCmdSetLineWidth glad_debug_vkCmdSetLineWidth = glad_debug_impl_vkCmdSetLineWidth;
PFN_vkCmdSetLogicOpEXT glad_vkCmdSetLogicOpEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetLogicOpEXT(VkCommandBuffer commandBuffer, VkLogicOp logicOp) {
    _pre_call_vulkan_callback("vkCmdSetLogicOpEXT", (GLADapiproc) glad_vkCmdSetLogicOpEXT, 2, commandBuffer, logicOp);
    glad_vkCmdSetLogicOpEXT(commandBuffer, logicOp);
    _post_call_vulkan_callback(NULL, "vkCmdSetLogicOpEXT", (GLADapiproc) glad_vkCmdSetLogicOpEXT, 2, commandBuffer, logicOp);
    
}
PFN_vkCmdSetLogicOpEXT glad_debug_vkCmdSetLogicOpEXT = glad_debug_impl_vkCmdSetLogicOpEXT;
PFN_vkCmdSetLogicOpEnableEXT glad_vkCmdSetLogicOpEnableEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetLogicOpEnableEXT(VkCommandBuffer commandBuffer, VkBool32 logicOpEnable) {
    _pre_call_vulkan_callback("vkCmdSetLogicOpEnableEXT", (GLADapiproc) glad_vkCmdSetLogicOpEnableEXT, 2, commandBuffer, logicOpEnable);
    glad_vkCmdSetLogicOpEnableEXT(commandBuffer, logicOpEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetLogicOpEnableEXT", (GLADapiproc) glad_vkCmdSetLogicOpEnableEXT, 2, commandBuffer, logicOpEnable);
    
}
PFN_vkCmdSetLogicOpEnableEXT glad_debug_vkCmdSetLogicOpEnableEXT = glad_debug_impl_vkCmdSetLogicOpEnableEXT;
PFN_vkCmdSetPatchControlPointsEXT glad_vkCmdSetPatchControlPointsEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetPatchControlPointsEXT(VkCommandBuffer commandBuffer, uint32_t patchControlPoints) {
    _pre_call_vulkan_callback("vkCmdSetPatchControlPointsEXT", (GLADapiproc) glad_vkCmdSetPatchControlPointsEXT, 2, commandBuffer, patchControlPoints);
    glad_vkCmdSetPatchControlPointsEXT(commandBuffer, patchControlPoints);
    _post_call_vulkan_callback(NULL, "vkCmdSetPatchControlPointsEXT", (GLADapiproc) glad_vkCmdSetPatchControlPointsEXT, 2, commandBuffer, patchControlPoints);
    
}
PFN_vkCmdSetPatchControlPointsEXT glad_debug_vkCmdSetPatchControlPointsEXT = glad_debug_impl_vkCmdSetPatchControlPointsEXT;
PFN_vkCmdSetPolygonModeEXT glad_vkCmdSetPolygonModeEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetPolygonModeEXT(VkCommandBuffer commandBuffer, VkPolygonMode polygonMode) {
    _pre_call_vulkan_callback("vkCmdSetPolygonModeEXT", (GLADapiproc) glad_vkCmdSetPolygonModeEXT, 2, commandBuffer, polygonMode);
    glad_vkCmdSetPolygonModeEXT(commandBuffer, polygonMode);
    _post_call_vulkan_callback(NULL, "vkCmdSetPolygonModeEXT", (GLADapiproc) glad_vkCmdSetPolygonModeEXT, 2, commandBuffer, polygonMode);
    
}
PFN_vkCmdSetPolygonModeEXT glad_debug_vkCmdSetPolygonModeEXT = glad_debug_impl_vkCmdSetPolygonModeEXT;
PFN_vkCmdSetPrimitiveRestartEnable glad_vkCmdSetPrimitiveRestartEnable = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetPrimitiveRestartEnable(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) {
    _pre_call_vulkan_callback("vkCmdSetPrimitiveRestartEnable", (GLADapiproc) glad_vkCmdSetPrimitiveRestartEnable, 2, commandBuffer, primitiveRestartEnable);
    glad_vkCmdSetPrimitiveRestartEnable(commandBuffer, primitiveRestartEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetPrimitiveRestartEnable", (GLADapiproc) glad_vkCmdSetPrimitiveRestartEnable, 2, commandBuffer, primitiveRestartEnable);
    
}
PFN_vkCmdSetPrimitiveRestartEnable glad_debug_vkCmdSetPrimitiveRestartEnable = glad_debug_impl_vkCmdSetPrimitiveRestartEnable;
PFN_vkCmdSetPrimitiveRestartEnableEXT glad_vkCmdSetPrimitiveRestartEnableEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetPrimitiveRestartEnableEXT(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) {
    _pre_call_vulkan_callback("vkCmdSetPrimitiveRestartEnableEXT", (GLADapiproc) glad_vkCmdSetPrimitiveRestartEnableEXT, 2, commandBuffer, primitiveRestartEnable);
    glad_vkCmdSetPrimitiveRestartEnableEXT(commandBuffer, primitiveRestartEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetPrimitiveRestartEnableEXT", (GLADapiproc) glad_vkCmdSetPrimitiveRestartEnableEXT, 2, commandBuffer, primitiveRestartEnable);
    
}
PFN_vkCmdSetPrimitiveRestartEnableEXT glad_debug_vkCmdSetPrimitiveRestartEnableEXT = glad_debug_impl_vkCmdSetPrimitiveRestartEnableEXT;
PFN_vkCmdSetPrimitiveTopology glad_vkCmdSetPrimitiveTopology = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetPrimitiveTopology(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) {
    _pre_call_vulkan_callback("vkCmdSetPrimitiveTopology", (GLADapiproc) glad_vkCmdSetPrimitiveTopology, 2, commandBuffer, primitiveTopology);
    glad_vkCmdSetPrimitiveTopology(commandBuffer, primitiveTopology);
    _post_call_vulkan_callback(NULL, "vkCmdSetPrimitiveTopology", (GLADapiproc) glad_vkCmdSetPrimitiveTopology, 2, commandBuffer, primitiveTopology);
    
}
PFN_vkCmdSetPrimitiveTopology glad_debug_vkCmdSetPrimitiveTopology = glad_debug_impl_vkCmdSetPrimitiveTopology;
PFN_vkCmdSetPrimitiveTopologyEXT glad_vkCmdSetPrimitiveTopologyEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetPrimitiveTopologyEXT(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) {
    _pre_call_vulkan_callback("vkCmdSetPrimitiveTopologyEXT", (GLADapiproc) glad_vkCmdSetPrimitiveTopologyEXT, 2, commandBuffer, primitiveTopology);
    glad_vkCmdSetPrimitiveTopologyEXT(commandBuffer, primitiveTopology);
    _post_call_vulkan_callback(NULL, "vkCmdSetPrimitiveTopologyEXT", (GLADapiproc) glad_vkCmdSetPrimitiveTopologyEXT, 2, commandBuffer, primitiveTopology);
    
}
PFN_vkCmdSetPrimitiveTopologyEXT glad_debug_vkCmdSetPrimitiveTopologyEXT = glad_debug_impl_vkCmdSetPrimitiveTopologyEXT;
PFN_vkCmdSetProvokingVertexModeEXT glad_vkCmdSetProvokingVertexModeEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetProvokingVertexModeEXT(VkCommandBuffer commandBuffer, VkProvokingVertexModeEXT provokingVertexMode) {
    _pre_call_vulkan_callback("vkCmdSetProvokingVertexModeEXT", (GLADapiproc) glad_vkCmdSetProvokingVertexModeEXT, 2, commandBuffer, provokingVertexMode);
    glad_vkCmdSetProvokingVertexModeEXT(commandBuffer, provokingVertexMode);
    _post_call_vulkan_callback(NULL, "vkCmdSetProvokingVertexModeEXT", (GLADapiproc) glad_vkCmdSetProvokingVertexModeEXT, 2, commandBuffer, provokingVertexMode);
    
}
PFN_vkCmdSetProvokingVertexModeEXT glad_debug_vkCmdSetProvokingVertexModeEXT = glad_debug_impl_vkCmdSetProvokingVertexModeEXT;
PFN_vkCmdSetRasterizationSamplesEXT glad_vkCmdSetRasterizationSamplesEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetRasterizationSamplesEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits rasterizationSamples) {
    _pre_call_vulkan_callback("vkCmdSetRasterizationSamplesEXT", (GLADapiproc) glad_vkCmdSetRasterizationSamplesEXT, 2, commandBuffer, rasterizationSamples);
    glad_vkCmdSetRasterizationSamplesEXT(commandBuffer, rasterizationSamples);
    _post_call_vulkan_callback(NULL, "vkCmdSetRasterizationSamplesEXT", (GLADapiproc) glad_vkCmdSetRasterizationSamplesEXT, 2, commandBuffer, rasterizationSamples);
    
}
PFN_vkCmdSetRasterizationSamplesEXT glad_debug_vkCmdSetRasterizationSamplesEXT = glad_debug_impl_vkCmdSetRasterizationSamplesEXT;
PFN_vkCmdSetRasterizationStreamEXT glad_vkCmdSetRasterizationStreamEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetRasterizationStreamEXT(VkCommandBuffer commandBuffer, uint32_t rasterizationStream) {
    _pre_call_vulkan_callback("vkCmdSetRasterizationStreamEXT", (GLADapiproc) glad_vkCmdSetRasterizationStreamEXT, 2, commandBuffer, rasterizationStream);
    glad_vkCmdSetRasterizationStreamEXT(commandBuffer, rasterizationStream);
    _post_call_vulkan_callback(NULL, "vkCmdSetRasterizationStreamEXT", (GLADapiproc) glad_vkCmdSetRasterizationStreamEXT, 2, commandBuffer, rasterizationStream);
    
}
PFN_vkCmdSetRasterizationStreamEXT glad_debug_vkCmdSetRasterizationStreamEXT = glad_debug_impl_vkCmdSetRasterizationStreamEXT;
PFN_vkCmdSetRasterizerDiscardEnable glad_vkCmdSetRasterizerDiscardEnable = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetRasterizerDiscardEnable(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) {
    _pre_call_vulkan_callback("vkCmdSetRasterizerDiscardEnable", (GLADapiproc) glad_vkCmdSetRasterizerDiscardEnable, 2, commandBuffer, rasterizerDiscardEnable);
    glad_vkCmdSetRasterizerDiscardEnable(commandBuffer, rasterizerDiscardEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetRasterizerDiscardEnable", (GLADapiproc) glad_vkCmdSetRasterizerDiscardEnable, 2, commandBuffer, rasterizerDiscardEnable);
    
}
PFN_vkCmdSetRasterizerDiscardEnable glad_debug_vkCmdSetRasterizerDiscardEnable = glad_debug_impl_vkCmdSetRasterizerDiscardEnable;
PFN_vkCmdSetRasterizerDiscardEnableEXT glad_vkCmdSetRasterizerDiscardEnableEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetRasterizerDiscardEnableEXT(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) {
    _pre_call_vulkan_callback("vkCmdSetRasterizerDiscardEnableEXT", (GLADapiproc) glad_vkCmdSetRasterizerDiscardEnableEXT, 2, commandBuffer, rasterizerDiscardEnable);
    glad_vkCmdSetRasterizerDiscardEnableEXT(commandBuffer, rasterizerDiscardEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetRasterizerDiscardEnableEXT", (GLADapiproc) glad_vkCmdSetRasterizerDiscardEnableEXT, 2, commandBuffer, rasterizerDiscardEnable);
    
}
PFN_vkCmdSetRasterizerDiscardEnableEXT glad_debug_vkCmdSetRasterizerDiscardEnableEXT = glad_debug_impl_vkCmdSetRasterizerDiscardEnableEXT;
PFN_vkCmdSetRenderingAttachmentLocations glad_vkCmdSetRenderingAttachmentLocations = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetRenderingAttachmentLocations(VkCommandBuffer commandBuffer, const VkRenderingAttachmentLocationInfo * pLocationInfo) {
    _pre_call_vulkan_callback("vkCmdSetRenderingAttachmentLocations", (GLADapiproc) glad_vkCmdSetRenderingAttachmentLocations, 2, commandBuffer, pLocationInfo);
    glad_vkCmdSetRenderingAttachmentLocations(commandBuffer, pLocationInfo);
    _post_call_vulkan_callback(NULL, "vkCmdSetRenderingAttachmentLocations", (GLADapiproc) glad_vkCmdSetRenderingAttachmentLocations, 2, commandBuffer, pLocationInfo);
    
}
PFN_vkCmdSetRenderingAttachmentLocations glad_debug_vkCmdSetRenderingAttachmentLocations = glad_debug_impl_vkCmdSetRenderingAttachmentLocations;
PFN_vkCmdSetRenderingAttachmentLocationsKHR glad_vkCmdSetRenderingAttachmentLocationsKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetRenderingAttachmentLocationsKHR(VkCommandBuffer commandBuffer, const VkRenderingAttachmentLocationInfo * pLocationInfo) {
    _pre_call_vulkan_callback("vkCmdSetRenderingAttachmentLocationsKHR", (GLADapiproc) glad_vkCmdSetRenderingAttachmentLocationsKHR, 2, commandBuffer, pLocationInfo);
    glad_vkCmdSetRenderingAttachmentLocationsKHR(commandBuffer, pLocationInfo);
    _post_call_vulkan_callback(NULL, "vkCmdSetRenderingAttachmentLocationsKHR", (GLADapiproc) glad_vkCmdSetRenderingAttachmentLocationsKHR, 2, commandBuffer, pLocationInfo);
    
}
PFN_vkCmdSetRenderingAttachmentLocationsKHR glad_debug_vkCmdSetRenderingAttachmentLocationsKHR = glad_debug_impl_vkCmdSetRenderingAttachmentLocationsKHR;
PFN_vkCmdSetRenderingInputAttachmentIndices glad_vkCmdSetRenderingInputAttachmentIndices = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetRenderingInputAttachmentIndices(VkCommandBuffer commandBuffer, const VkRenderingInputAttachmentIndexInfo * pInputAttachmentIndexInfo) {
    _pre_call_vulkan_callback("vkCmdSetRenderingInputAttachmentIndices", (GLADapiproc) glad_vkCmdSetRenderingInputAttachmentIndices, 2, commandBuffer, pInputAttachmentIndexInfo);
    glad_vkCmdSetRenderingInputAttachmentIndices(commandBuffer, pInputAttachmentIndexInfo);
    _post_call_vulkan_callback(NULL, "vkCmdSetRenderingInputAttachmentIndices", (GLADapiproc) glad_vkCmdSetRenderingInputAttachmentIndices, 2, commandBuffer, pInputAttachmentIndexInfo);
    
}
PFN_vkCmdSetRenderingInputAttachmentIndices glad_debug_vkCmdSetRenderingInputAttachmentIndices = glad_debug_impl_vkCmdSetRenderingInputAttachmentIndices;
PFN_vkCmdSetRenderingInputAttachmentIndicesKHR glad_vkCmdSetRenderingInputAttachmentIndicesKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetRenderingInputAttachmentIndicesKHR(VkCommandBuffer commandBuffer, const VkRenderingInputAttachmentIndexInfo * pInputAttachmentIndexInfo) {
    _pre_call_vulkan_callback("vkCmdSetRenderingInputAttachmentIndicesKHR", (GLADapiproc) glad_vkCmdSetRenderingInputAttachmentIndicesKHR, 2, commandBuffer, pInputAttachmentIndexInfo);
    glad_vkCmdSetRenderingInputAttachmentIndicesKHR(commandBuffer, pInputAttachmentIndexInfo);
    _post_call_vulkan_callback(NULL, "vkCmdSetRenderingInputAttachmentIndicesKHR", (GLADapiproc) glad_vkCmdSetRenderingInputAttachmentIndicesKHR, 2, commandBuffer, pInputAttachmentIndexInfo);
    
}
PFN_vkCmdSetRenderingInputAttachmentIndicesKHR glad_debug_vkCmdSetRenderingInputAttachmentIndicesKHR = glad_debug_impl_vkCmdSetRenderingInputAttachmentIndicesKHR;
PFN_vkCmdSetRepresentativeFragmentTestEnableNV glad_vkCmdSetRepresentativeFragmentTestEnableNV = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetRepresentativeFragmentTestEnableNV(VkCommandBuffer commandBuffer, VkBool32 representativeFragmentTestEnable) {
    _pre_call_vulkan_callback("vkCmdSetRepresentativeFragmentTestEnableNV", (GLADapiproc) glad_vkCmdSetRepresentativeFragmentTestEnableNV, 2, commandBuffer, representativeFragmentTestEnable);
    glad_vkCmdSetRepresentativeFragmentTestEnableNV(commandBuffer, representativeFragmentTestEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetRepresentativeFragmentTestEnableNV", (GLADapiproc) glad_vkCmdSetRepresentativeFragmentTestEnableNV, 2, commandBuffer, representativeFragmentTestEnable);
    
}
PFN_vkCmdSetRepresentativeFragmentTestEnableNV glad_debug_vkCmdSetRepresentativeFragmentTestEnableNV = glad_debug_impl_vkCmdSetRepresentativeFragmentTestEnableNV;
PFN_vkCmdSetSampleLocationsEnableEXT glad_vkCmdSetSampleLocationsEnableEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetSampleLocationsEnableEXT(VkCommandBuffer commandBuffer, VkBool32 sampleLocationsEnable) {
    _pre_call_vulkan_callback("vkCmdSetSampleLocationsEnableEXT", (GLADapiproc) glad_vkCmdSetSampleLocationsEnableEXT, 2, commandBuffer, sampleLocationsEnable);
    glad_vkCmdSetSampleLocationsEnableEXT(commandBuffer, sampleLocationsEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetSampleLocationsEnableEXT", (GLADapiproc) glad_vkCmdSetSampleLocationsEnableEXT, 2, commandBuffer, sampleLocationsEnable);
    
}
PFN_vkCmdSetSampleLocationsEnableEXT glad_debug_vkCmdSetSampleLocationsEnableEXT = glad_debug_impl_vkCmdSetSampleLocationsEnableEXT;
PFN_vkCmdSetSampleMaskEXT glad_vkCmdSetSampleMaskEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetSampleMaskEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits samples, const VkSampleMask * pSampleMask) {
    _pre_call_vulkan_callback("vkCmdSetSampleMaskEXT", (GLADapiproc) glad_vkCmdSetSampleMaskEXT, 3, commandBuffer, samples, pSampleMask);
    glad_vkCmdSetSampleMaskEXT(commandBuffer, samples, pSampleMask);
    _post_call_vulkan_callback(NULL, "vkCmdSetSampleMaskEXT", (GLADapiproc) glad_vkCmdSetSampleMaskEXT, 3, commandBuffer, samples, pSampleMask);
    
}
PFN_vkCmdSetSampleMaskEXT glad_debug_vkCmdSetSampleMaskEXT = glad_debug_impl_vkCmdSetSampleMaskEXT;
PFN_vkCmdSetScissor glad_vkCmdSetScissor = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D * pScissors) {
    _pre_call_vulkan_callback("vkCmdSetScissor", (GLADapiproc) glad_vkCmdSetScissor, 4, commandBuffer, firstScissor, scissorCount, pScissors);
    glad_vkCmdSetScissor(commandBuffer, firstScissor, scissorCount, pScissors);
    _post_call_vulkan_callback(NULL, "vkCmdSetScissor", (GLADapiproc) glad_vkCmdSetScissor, 4, commandBuffer, firstScissor, scissorCount, pScissors);
    
}
PFN_vkCmdSetScissor glad_debug_vkCmdSetScissor = glad_debug_impl_vkCmdSetScissor;
PFN_vkCmdSetScissorWithCount glad_vkCmdSetScissorWithCount = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetScissorWithCount(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D * pScissors) {
    _pre_call_vulkan_callback("vkCmdSetScissorWithCount", (GLADapiproc) glad_vkCmdSetScissorWithCount, 3, commandBuffer, scissorCount, pScissors);
    glad_vkCmdSetScissorWithCount(commandBuffer, scissorCount, pScissors);
    _post_call_vulkan_callback(NULL, "vkCmdSetScissorWithCount", (GLADapiproc) glad_vkCmdSetScissorWithCount, 3, commandBuffer, scissorCount, pScissors);
    
}
PFN_vkCmdSetScissorWithCount glad_debug_vkCmdSetScissorWithCount = glad_debug_impl_vkCmdSetScissorWithCount;
PFN_vkCmdSetScissorWithCountEXT glad_vkCmdSetScissorWithCountEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetScissorWithCountEXT(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D * pScissors) {
    _pre_call_vulkan_callback("vkCmdSetScissorWithCountEXT", (GLADapiproc) glad_vkCmdSetScissorWithCountEXT, 3, commandBuffer, scissorCount, pScissors);
    glad_vkCmdSetScissorWithCountEXT(commandBuffer, scissorCount, pScissors);
    _post_call_vulkan_callback(NULL, "vkCmdSetScissorWithCountEXT", (GLADapiproc) glad_vkCmdSetScissorWithCountEXT, 3, commandBuffer, scissorCount, pScissors);
    
}
PFN_vkCmdSetScissorWithCountEXT glad_debug_vkCmdSetScissorWithCountEXT = glad_debug_impl_vkCmdSetScissorWithCountEXT;
PFN_vkCmdSetShadingRateImageEnableNV glad_vkCmdSetShadingRateImageEnableNV = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetShadingRateImageEnableNV(VkCommandBuffer commandBuffer, VkBool32 shadingRateImageEnable) {
    _pre_call_vulkan_callback("vkCmdSetShadingRateImageEnableNV", (GLADapiproc) glad_vkCmdSetShadingRateImageEnableNV, 2, commandBuffer, shadingRateImageEnable);
    glad_vkCmdSetShadingRateImageEnableNV(commandBuffer, shadingRateImageEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetShadingRateImageEnableNV", (GLADapiproc) glad_vkCmdSetShadingRateImageEnableNV, 2, commandBuffer, shadingRateImageEnable);
    
}
PFN_vkCmdSetShadingRateImageEnableNV glad_debug_vkCmdSetShadingRateImageEnableNV = glad_debug_impl_vkCmdSetShadingRateImageEnableNV;
PFN_vkCmdSetStencilCompareMask glad_vkCmdSetStencilCompareMask = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) {
    _pre_call_vulkan_callback("vkCmdSetStencilCompareMask", (GLADapiproc) glad_vkCmdSetStencilCompareMask, 3, commandBuffer, faceMask, compareMask);
    glad_vkCmdSetStencilCompareMask(commandBuffer, faceMask, compareMask);
    _post_call_vulkan_callback(NULL, "vkCmdSetStencilCompareMask", (GLADapiproc) glad_vkCmdSetStencilCompareMask, 3, commandBuffer, faceMask, compareMask);
    
}
PFN_vkCmdSetStencilCompareMask glad_debug_vkCmdSetStencilCompareMask = glad_debug_impl_vkCmdSetStencilCompareMask;
PFN_vkCmdSetStencilOp glad_vkCmdSetStencilOp = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetStencilOp(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) {
    _pre_call_vulkan_callback("vkCmdSetStencilOp", (GLADapiproc) glad_vkCmdSetStencilOp, 6, commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
    glad_vkCmdSetStencilOp(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
    _post_call_vulkan_callback(NULL, "vkCmdSetStencilOp", (GLADapiproc) glad_vkCmdSetStencilOp, 6, commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
    
}
PFN_vkCmdSetStencilOp glad_debug_vkCmdSetStencilOp = glad_debug_impl_vkCmdSetStencilOp;
PFN_vkCmdSetStencilOpEXT glad_vkCmdSetStencilOpEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetStencilOpEXT(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) {
    _pre_call_vulkan_callback("vkCmdSetStencilOpEXT", (GLADapiproc) glad_vkCmdSetStencilOpEXT, 6, commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
    glad_vkCmdSetStencilOpEXT(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
    _post_call_vulkan_callback(NULL, "vkCmdSetStencilOpEXT", (GLADapiproc) glad_vkCmdSetStencilOpEXT, 6, commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
    
}
PFN_vkCmdSetStencilOpEXT glad_debug_vkCmdSetStencilOpEXT = glad_debug_impl_vkCmdSetStencilOpEXT;
PFN_vkCmdSetStencilReference glad_vkCmdSetStencilReference = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) {
    _pre_call_vulkan_callback("vkCmdSetStencilReference", (GLADapiproc) glad_vkCmdSetStencilReference, 3, commandBuffer, faceMask, reference);
    glad_vkCmdSetStencilReference(commandBuffer, faceMask, reference);
    _post_call_vulkan_callback(NULL, "vkCmdSetStencilReference", (GLADapiproc) glad_vkCmdSetStencilReference, 3, commandBuffer, faceMask, reference);
    
}
PFN_vkCmdSetStencilReference glad_debug_vkCmdSetStencilReference = glad_debug_impl_vkCmdSetStencilReference;
PFN_vkCmdSetStencilTestEnable glad_vkCmdSetStencilTestEnable = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetStencilTestEnable(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) {
    _pre_call_vulkan_callback("vkCmdSetStencilTestEnable", (GLADapiproc) glad_vkCmdSetStencilTestEnable, 2, commandBuffer, stencilTestEnable);
    glad_vkCmdSetStencilTestEnable(commandBuffer, stencilTestEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetStencilTestEnable", (GLADapiproc) glad_vkCmdSetStencilTestEnable, 2, commandBuffer, stencilTestEnable);
    
}
PFN_vkCmdSetStencilTestEnable glad_debug_vkCmdSetStencilTestEnable = glad_debug_impl_vkCmdSetStencilTestEnable;
PFN_vkCmdSetStencilTestEnableEXT glad_vkCmdSetStencilTestEnableEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetStencilTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) {
    _pre_call_vulkan_callback("vkCmdSetStencilTestEnableEXT", (GLADapiproc) glad_vkCmdSetStencilTestEnableEXT, 2, commandBuffer, stencilTestEnable);
    glad_vkCmdSetStencilTestEnableEXT(commandBuffer, stencilTestEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetStencilTestEnableEXT", (GLADapiproc) glad_vkCmdSetStencilTestEnableEXT, 2, commandBuffer, stencilTestEnable);
    
}
PFN_vkCmdSetStencilTestEnableEXT glad_debug_vkCmdSetStencilTestEnableEXT = glad_debug_impl_vkCmdSetStencilTestEnableEXT;
PFN_vkCmdSetStencilWriteMask glad_vkCmdSetStencilWriteMask = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) {
    _pre_call_vulkan_callback("vkCmdSetStencilWriteMask", (GLADapiproc) glad_vkCmdSetStencilWriteMask, 3, commandBuffer, faceMask, writeMask);
    glad_vkCmdSetStencilWriteMask(commandBuffer, faceMask, writeMask);
    _post_call_vulkan_callback(NULL, "vkCmdSetStencilWriteMask", (GLADapiproc) glad_vkCmdSetStencilWriteMask, 3, commandBuffer, faceMask, writeMask);
    
}
PFN_vkCmdSetStencilWriteMask glad_debug_vkCmdSetStencilWriteMask = glad_debug_impl_vkCmdSetStencilWriteMask;
PFN_vkCmdSetTessellationDomainOriginEXT glad_vkCmdSetTessellationDomainOriginEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetTessellationDomainOriginEXT(VkCommandBuffer commandBuffer, VkTessellationDomainOrigin domainOrigin) {
    _pre_call_vulkan_callback("vkCmdSetTessellationDomainOriginEXT", (GLADapiproc) glad_vkCmdSetTessellationDomainOriginEXT, 2, commandBuffer, domainOrigin);
    glad_vkCmdSetTessellationDomainOriginEXT(commandBuffer, domainOrigin);
    _post_call_vulkan_callback(NULL, "vkCmdSetTessellationDomainOriginEXT", (GLADapiproc) glad_vkCmdSetTessellationDomainOriginEXT, 2, commandBuffer, domainOrigin);
    
}
PFN_vkCmdSetTessellationDomainOriginEXT glad_debug_vkCmdSetTessellationDomainOriginEXT = glad_debug_impl_vkCmdSetTessellationDomainOriginEXT;
PFN_vkCmdSetVertexInputEXT glad_vkCmdSetVertexInputEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetVertexInputEXT(VkCommandBuffer commandBuffer, uint32_t vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT * pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT * pVertexAttributeDescriptions) {
    _pre_call_vulkan_callback("vkCmdSetVertexInputEXT", (GLADapiproc) glad_vkCmdSetVertexInputEXT, 5, commandBuffer, vertexBindingDescriptionCount, pVertexBindingDescriptions, vertexAttributeDescriptionCount, pVertexAttributeDescriptions);
    glad_vkCmdSetVertexInputEXT(commandBuffer, vertexBindingDescriptionCount, pVertexBindingDescriptions, vertexAttributeDescriptionCount, pVertexAttributeDescriptions);
    _post_call_vulkan_callback(NULL, "vkCmdSetVertexInputEXT", (GLADapiproc) glad_vkCmdSetVertexInputEXT, 5, commandBuffer, vertexBindingDescriptionCount, pVertexBindingDescriptions, vertexAttributeDescriptionCount, pVertexAttributeDescriptions);
    
}
PFN_vkCmdSetVertexInputEXT glad_debug_vkCmdSetVertexInputEXT = glad_debug_impl_vkCmdSetVertexInputEXT;
PFN_vkCmdSetViewport glad_vkCmdSetViewport = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport * pViewports) {
    _pre_call_vulkan_callback("vkCmdSetViewport", (GLADapiproc) glad_vkCmdSetViewport, 4, commandBuffer, firstViewport, viewportCount, pViewports);
    glad_vkCmdSetViewport(commandBuffer, firstViewport, viewportCount, pViewports);
    _post_call_vulkan_callback(NULL, "vkCmdSetViewport", (GLADapiproc) glad_vkCmdSetViewport, 4, commandBuffer, firstViewport, viewportCount, pViewports);
    
}
PFN_vkCmdSetViewport glad_debug_vkCmdSetViewport = glad_debug_impl_vkCmdSetViewport;
PFN_vkCmdSetViewportSwizzleNV glad_vkCmdSetViewportSwizzleNV = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetViewportSwizzleNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportSwizzleNV * pViewportSwizzles) {
    _pre_call_vulkan_callback("vkCmdSetViewportSwizzleNV", (GLADapiproc) glad_vkCmdSetViewportSwizzleNV, 4, commandBuffer, firstViewport, viewportCount, pViewportSwizzles);
    glad_vkCmdSetViewportSwizzleNV(commandBuffer, firstViewport, viewportCount, pViewportSwizzles);
    _post_call_vulkan_callback(NULL, "vkCmdSetViewportSwizzleNV", (GLADapiproc) glad_vkCmdSetViewportSwizzleNV, 4, commandBuffer, firstViewport, viewportCount, pViewportSwizzles);
    
}
PFN_vkCmdSetViewportSwizzleNV glad_debug_vkCmdSetViewportSwizzleNV = glad_debug_impl_vkCmdSetViewportSwizzleNV;
PFN_vkCmdSetViewportWScalingEnableNV glad_vkCmdSetViewportWScalingEnableNV = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetViewportWScalingEnableNV(VkCommandBuffer commandBuffer, VkBool32 viewportWScalingEnable) {
    _pre_call_vulkan_callback("vkCmdSetViewportWScalingEnableNV", (GLADapiproc) glad_vkCmdSetViewportWScalingEnableNV, 2, commandBuffer, viewportWScalingEnable);
    glad_vkCmdSetViewportWScalingEnableNV(commandBuffer, viewportWScalingEnable);
    _post_call_vulkan_callback(NULL, "vkCmdSetViewportWScalingEnableNV", (GLADapiproc) glad_vkCmdSetViewportWScalingEnableNV, 2, commandBuffer, viewportWScalingEnable);
    
}
PFN_vkCmdSetViewportWScalingEnableNV glad_debug_vkCmdSetViewportWScalingEnableNV = glad_debug_impl_vkCmdSetViewportWScalingEnableNV;
PFN_vkCmdSetViewportWithCount glad_vkCmdSetViewportWithCount = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetViewportWithCount(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport * pViewports) {
    _pre_call_vulkan_callback("vkCmdSetViewportWithCount", (GLADapiproc) glad_vkCmdSetViewportWithCount, 3, commandBuffer, viewportCount, pViewports);
    glad_vkCmdSetViewportWithCount(commandBuffer, viewportCount, pViewports);
    _post_call_vulkan_callback(NULL, "vkCmdSetViewportWithCount", (GLADapiproc) glad_vkCmdSetViewportWithCount, 3, commandBuffer, viewportCount, pViewports);
    
}
PFN_vkCmdSetViewportWithCount glad_debug_vkCmdSetViewportWithCount = glad_debug_impl_vkCmdSetViewportWithCount;
PFN_vkCmdSetViewportWithCountEXT glad_vkCmdSetViewportWithCountEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdSetViewportWithCountEXT(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport * pViewports) {
    _pre_call_vulkan_callback("vkCmdSetViewportWithCountEXT", (GLADapiproc) glad_vkCmdSetViewportWithCountEXT, 3, commandBuffer, viewportCount, pViewports);
    glad_vkCmdSetViewportWithCountEXT(commandBuffer, viewportCount, pViewports);
    _post_call_vulkan_callback(NULL, "vkCmdSetViewportWithCountEXT", (GLADapiproc) glad_vkCmdSetViewportWithCountEXT, 3, commandBuffer, viewportCount, pViewports);
    
}
PFN_vkCmdSetViewportWithCountEXT glad_debug_vkCmdSetViewportWithCountEXT = glad_debug_impl_vkCmdSetViewportWithCountEXT;
PFN_vkCmdUpdateBuffer glad_vkCmdUpdateBuffer = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void * pData) {
    _pre_call_vulkan_callback("vkCmdUpdateBuffer", (GLADapiproc) glad_vkCmdUpdateBuffer, 5, commandBuffer, dstBuffer, dstOffset, dataSize, pData);
    glad_vkCmdUpdateBuffer(commandBuffer, dstBuffer, dstOffset, dataSize, pData);
    _post_call_vulkan_callback(NULL, "vkCmdUpdateBuffer", (GLADapiproc) glad_vkCmdUpdateBuffer, 5, commandBuffer, dstBuffer, dstOffset, dataSize, pData);
    
}
PFN_vkCmdUpdateBuffer glad_debug_vkCmdUpdateBuffer = glad_debug_impl_vkCmdUpdateBuffer;
PFN_vkCmdWaitEvents glad_vkCmdWaitEvents = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent * pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier * pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier * pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier * pImageMemoryBarriers) {
    _pre_call_vulkan_callback("vkCmdWaitEvents", (GLADapiproc) glad_vkCmdWaitEvents, 11, commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    glad_vkCmdWaitEvents(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    _post_call_vulkan_callback(NULL, "vkCmdWaitEvents", (GLADapiproc) glad_vkCmdWaitEvents, 11, commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
    
}
PFN_vkCmdWaitEvents glad_debug_vkCmdWaitEvents = glad_debug_impl_vkCmdWaitEvents;
PFN_vkCmdWaitEvents2 glad_vkCmdWaitEvents2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdWaitEvents2(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent * pEvents, const VkDependencyInfo * pDependencyInfos) {
    _pre_call_vulkan_callback("vkCmdWaitEvents2", (GLADapiproc) glad_vkCmdWaitEvents2, 4, commandBuffer, eventCount, pEvents, pDependencyInfos);
    glad_vkCmdWaitEvents2(commandBuffer, eventCount, pEvents, pDependencyInfos);
    _post_call_vulkan_callback(NULL, "vkCmdWaitEvents2", (GLADapiproc) glad_vkCmdWaitEvents2, 4, commandBuffer, eventCount, pEvents, pDependencyInfos);
    
}
PFN_vkCmdWaitEvents2 glad_debug_vkCmdWaitEvents2 = glad_debug_impl_vkCmdWaitEvents2;
PFN_vkCmdWaitEvents2KHR glad_vkCmdWaitEvents2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdWaitEvents2KHR(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent * pEvents, const VkDependencyInfo * pDependencyInfos) {
    _pre_call_vulkan_callback("vkCmdWaitEvents2KHR", (GLADapiproc) glad_vkCmdWaitEvents2KHR, 4, commandBuffer, eventCount, pEvents, pDependencyInfos);
    glad_vkCmdWaitEvents2KHR(commandBuffer, eventCount, pEvents, pDependencyInfos);
    _post_call_vulkan_callback(NULL, "vkCmdWaitEvents2KHR", (GLADapiproc) glad_vkCmdWaitEvents2KHR, 4, commandBuffer, eventCount, pEvents, pDependencyInfos);
    
}
PFN_vkCmdWaitEvents2KHR glad_debug_vkCmdWaitEvents2KHR = glad_debug_impl_vkCmdWaitEvents2KHR;
PFN_vkCmdWriteTimestamp glad_vkCmdWriteTimestamp = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) {
    _pre_call_vulkan_callback("vkCmdWriteTimestamp", (GLADapiproc) glad_vkCmdWriteTimestamp, 4, commandBuffer, pipelineStage, queryPool, query);
    glad_vkCmdWriteTimestamp(commandBuffer, pipelineStage, queryPool, query);
    _post_call_vulkan_callback(NULL, "vkCmdWriteTimestamp", (GLADapiproc) glad_vkCmdWriteTimestamp, 4, commandBuffer, pipelineStage, queryPool, query);
    
}
PFN_vkCmdWriteTimestamp glad_debug_vkCmdWriteTimestamp = glad_debug_impl_vkCmdWriteTimestamp;
PFN_vkCmdWriteTimestamp2 glad_vkCmdWriteTimestamp2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdWriteTimestamp2(VkCommandBuffer commandBuffer, VkPipelineStageFlags2 stage, VkQueryPool queryPool, uint32_t query) {
    _pre_call_vulkan_callback("vkCmdWriteTimestamp2", (GLADapiproc) glad_vkCmdWriteTimestamp2, 4, commandBuffer, stage, queryPool, query);
    glad_vkCmdWriteTimestamp2(commandBuffer, stage, queryPool, query);
    _post_call_vulkan_callback(NULL, "vkCmdWriteTimestamp2", (GLADapiproc) glad_vkCmdWriteTimestamp2, 4, commandBuffer, stage, queryPool, query);
    
}
PFN_vkCmdWriteTimestamp2 glad_debug_vkCmdWriteTimestamp2 = glad_debug_impl_vkCmdWriteTimestamp2;
PFN_vkCmdWriteTimestamp2KHR glad_vkCmdWriteTimestamp2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkCmdWriteTimestamp2KHR(VkCommandBuffer commandBuffer, VkPipelineStageFlags2 stage, VkQueryPool queryPool, uint32_t query) {
    _pre_call_vulkan_callback("vkCmdWriteTimestamp2KHR", (GLADapiproc) glad_vkCmdWriteTimestamp2KHR, 4, commandBuffer, stage, queryPool, query);
    glad_vkCmdWriteTimestamp2KHR(commandBuffer, stage, queryPool, query);
    _post_call_vulkan_callback(NULL, "vkCmdWriteTimestamp2KHR", (GLADapiproc) glad_vkCmdWriteTimestamp2KHR, 4, commandBuffer, stage, queryPool, query);
    
}
PFN_vkCmdWriteTimestamp2KHR glad_debug_vkCmdWriteTimestamp2KHR = glad_debug_impl_vkCmdWriteTimestamp2KHR;
PFN_vkCopyImageToImage glad_vkCopyImageToImage = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCopyImageToImage(VkDevice device, const VkCopyImageToImageInfo * pCopyImageToImageInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCopyImageToImage", (GLADapiproc) glad_vkCopyImageToImage, 2, device, pCopyImageToImageInfo);
    ret = glad_vkCopyImageToImage(device, pCopyImageToImageInfo);
    _post_call_vulkan_callback((void*) &ret, "vkCopyImageToImage", (GLADapiproc) glad_vkCopyImageToImage, 2, device, pCopyImageToImageInfo);
    return ret;
}
PFN_vkCopyImageToImage glad_debug_vkCopyImageToImage = glad_debug_impl_vkCopyImageToImage;
PFN_vkCopyImageToImageEXT glad_vkCopyImageToImageEXT = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCopyImageToImageEXT(VkDevice device, const VkCopyImageToImageInfo * pCopyImageToImageInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCopyImageToImageEXT", (GLADapiproc) glad_vkCopyImageToImageEXT, 2, device, pCopyImageToImageInfo);
    ret = glad_vkCopyImageToImageEXT(device, pCopyImageToImageInfo);
    _post_call_vulkan_callback((void*) &ret, "vkCopyImageToImageEXT", (GLADapiproc) glad_vkCopyImageToImageEXT, 2, device, pCopyImageToImageInfo);
    return ret;
}
PFN_vkCopyImageToImageEXT glad_debug_vkCopyImageToImageEXT = glad_debug_impl_vkCopyImageToImageEXT;
PFN_vkCopyImageToMemory glad_vkCopyImageToMemory = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCopyImageToMemory(VkDevice device, const VkCopyImageToMemoryInfo * pCopyImageToMemoryInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCopyImageToMemory", (GLADapiproc) glad_vkCopyImageToMemory, 2, device, pCopyImageToMemoryInfo);
    ret = glad_vkCopyImageToMemory(device, pCopyImageToMemoryInfo);
    _post_call_vulkan_callback((void*) &ret, "vkCopyImageToMemory", (GLADapiproc) glad_vkCopyImageToMemory, 2, device, pCopyImageToMemoryInfo);
    return ret;
}
PFN_vkCopyImageToMemory glad_debug_vkCopyImageToMemory = glad_debug_impl_vkCopyImageToMemory;
PFN_vkCopyImageToMemoryEXT glad_vkCopyImageToMemoryEXT = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCopyImageToMemoryEXT(VkDevice device, const VkCopyImageToMemoryInfo * pCopyImageToMemoryInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCopyImageToMemoryEXT", (GLADapiproc) glad_vkCopyImageToMemoryEXT, 2, device, pCopyImageToMemoryInfo);
    ret = glad_vkCopyImageToMemoryEXT(device, pCopyImageToMemoryInfo);
    _post_call_vulkan_callback((void*) &ret, "vkCopyImageToMemoryEXT", (GLADapiproc) glad_vkCopyImageToMemoryEXT, 2, device, pCopyImageToMemoryInfo);
    return ret;
}
PFN_vkCopyImageToMemoryEXT glad_debug_vkCopyImageToMemoryEXT = glad_debug_impl_vkCopyImageToMemoryEXT;
PFN_vkCopyMemoryToImage glad_vkCopyMemoryToImage = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCopyMemoryToImage(VkDevice device, const VkCopyMemoryToImageInfo * pCopyMemoryToImageInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCopyMemoryToImage", (GLADapiproc) glad_vkCopyMemoryToImage, 2, device, pCopyMemoryToImageInfo);
    ret = glad_vkCopyMemoryToImage(device, pCopyMemoryToImageInfo);
    _post_call_vulkan_callback((void*) &ret, "vkCopyMemoryToImage", (GLADapiproc) glad_vkCopyMemoryToImage, 2, device, pCopyMemoryToImageInfo);
    return ret;
}
PFN_vkCopyMemoryToImage glad_debug_vkCopyMemoryToImage = glad_debug_impl_vkCopyMemoryToImage;
PFN_vkCopyMemoryToImageEXT glad_vkCopyMemoryToImageEXT = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCopyMemoryToImageEXT(VkDevice device, const VkCopyMemoryToImageInfo * pCopyMemoryToImageInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCopyMemoryToImageEXT", (GLADapiproc) glad_vkCopyMemoryToImageEXT, 2, device, pCopyMemoryToImageInfo);
    ret = glad_vkCopyMemoryToImageEXT(device, pCopyMemoryToImageInfo);
    _post_call_vulkan_callback((void*) &ret, "vkCopyMemoryToImageEXT", (GLADapiproc) glad_vkCopyMemoryToImageEXT, 2, device, pCopyMemoryToImageInfo);
    return ret;
}
PFN_vkCopyMemoryToImageEXT glad_debug_vkCopyMemoryToImageEXT = glad_debug_impl_vkCopyMemoryToImageEXT;
PFN_vkCreateBuffer glad_vkCreateBuffer = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateBuffer(VkDevice device, const VkBufferCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkBuffer * pBuffer) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateBuffer", (GLADapiproc) glad_vkCreateBuffer, 4, device, pCreateInfo, pAllocator, pBuffer);
    ret = glad_vkCreateBuffer(device, pCreateInfo, pAllocator, pBuffer);
    _post_call_vulkan_callback((void*) &ret, "vkCreateBuffer", (GLADapiproc) glad_vkCreateBuffer, 4, device, pCreateInfo, pAllocator, pBuffer);
    return ret;
}
PFN_vkCreateBuffer glad_debug_vkCreateBuffer = glad_debug_impl_vkCreateBuffer;
PFN_vkCreateBufferView glad_vkCreateBufferView = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateBufferView(VkDevice device, const VkBufferViewCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkBufferView * pView) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateBufferView", (GLADapiproc) glad_vkCreateBufferView, 4, device, pCreateInfo, pAllocator, pView);
    ret = glad_vkCreateBufferView(device, pCreateInfo, pAllocator, pView);
    _post_call_vulkan_callback((void*) &ret, "vkCreateBufferView", (GLADapiproc) glad_vkCreateBufferView, 4, device, pCreateInfo, pAllocator, pView);
    return ret;
}
PFN_vkCreateBufferView glad_debug_vkCreateBufferView = glad_debug_impl_vkCreateBufferView;
PFN_vkCreateCommandPool glad_vkCreateCommandPool = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkCommandPool * pCommandPool) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateCommandPool", (GLADapiproc) glad_vkCreateCommandPool, 4, device, pCreateInfo, pAllocator, pCommandPool);
    ret = glad_vkCreateCommandPool(device, pCreateInfo, pAllocator, pCommandPool);
    _post_call_vulkan_callback((void*) &ret, "vkCreateCommandPool", (GLADapiproc) glad_vkCreateCommandPool, 4, device, pCreateInfo, pAllocator, pCommandPool);
    return ret;
}
PFN_vkCreateCommandPool glad_debug_vkCreateCommandPool = glad_debug_impl_vkCreateCommandPool;
PFN_vkCreateComputePipelines glad_vkCreateComputePipelines = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo * pCreateInfos, const VkAllocationCallbacks * pAllocator, VkPipeline * pPipelines) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateComputePipelines", (GLADapiproc) glad_vkCreateComputePipelines, 6, device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    ret = glad_vkCreateComputePipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    _post_call_vulkan_callback((void*) &ret, "vkCreateComputePipelines", (GLADapiproc) glad_vkCreateComputePipelines, 6, device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    return ret;
}
PFN_vkCreateComputePipelines glad_debug_vkCreateComputePipelines = glad_debug_impl_vkCreateComputePipelines;
PFN_vkCreateDescriptorPool glad_vkCreateDescriptorPool = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDescriptorPool * pDescriptorPool) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateDescriptorPool", (GLADapiproc) glad_vkCreateDescriptorPool, 4, device, pCreateInfo, pAllocator, pDescriptorPool);
    ret = glad_vkCreateDescriptorPool(device, pCreateInfo, pAllocator, pDescriptorPool);
    _post_call_vulkan_callback((void*) &ret, "vkCreateDescriptorPool", (GLADapiproc) glad_vkCreateDescriptorPool, 4, device, pCreateInfo, pAllocator, pDescriptorPool);
    return ret;
}
PFN_vkCreateDescriptorPool glad_debug_vkCreateDescriptorPool = glad_debug_impl_vkCreateDescriptorPool;
PFN_vkCreateDescriptorSetLayout glad_vkCreateDescriptorSetLayout = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDescriptorSetLayout * pSetLayout) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateDescriptorSetLayout", (GLADapiproc) glad_vkCreateDescriptorSetLayout, 4, device, pCreateInfo, pAllocator, pSetLayout);
    ret = glad_vkCreateDescriptorSetLayout(device, pCreateInfo, pAllocator, pSetLayout);
    _post_call_vulkan_callback((void*) &ret, "vkCreateDescriptorSetLayout", (GLADapiproc) glad_vkCreateDescriptorSetLayout, 4, device, pCreateInfo, pAllocator, pSetLayout);
    return ret;
}
PFN_vkCreateDescriptorSetLayout glad_debug_vkCreateDescriptorSetLayout = glad_debug_impl_vkCreateDescriptorSetLayout;
PFN_vkCreateDescriptorUpdateTemplate glad_vkCreateDescriptorUpdateTemplate = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDescriptorUpdateTemplate * pDescriptorUpdateTemplate) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateDescriptorUpdateTemplate", (GLADapiproc) glad_vkCreateDescriptorUpdateTemplate, 4, device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
    ret = glad_vkCreateDescriptorUpdateTemplate(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
    _post_call_vulkan_callback((void*) &ret, "vkCreateDescriptorUpdateTemplate", (GLADapiproc) glad_vkCreateDescriptorUpdateTemplate, 4, device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
    return ret;
}
PFN_vkCreateDescriptorUpdateTemplate glad_debug_vkCreateDescriptorUpdateTemplate = glad_debug_impl_vkCreateDescriptorUpdateTemplate;
PFN_vkCreateDescriptorUpdateTemplateKHR glad_vkCreateDescriptorUpdateTemplateKHR = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateDescriptorUpdateTemplateKHR(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDescriptorUpdateTemplate * pDescriptorUpdateTemplate) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateDescriptorUpdateTemplateKHR", (GLADapiproc) glad_vkCreateDescriptorUpdateTemplateKHR, 4, device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
    ret = glad_vkCreateDescriptorUpdateTemplateKHR(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
    _post_call_vulkan_callback((void*) &ret, "vkCreateDescriptorUpdateTemplateKHR", (GLADapiproc) glad_vkCreateDescriptorUpdateTemplateKHR, 4, device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
    return ret;
}
PFN_vkCreateDescriptorUpdateTemplateKHR glad_debug_vkCreateDescriptorUpdateTemplateKHR = glad_debug_impl_vkCreateDescriptorUpdateTemplateKHR;
PFN_vkCreateDevice glad_vkCreateDevice = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDevice * pDevice) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateDevice", (GLADapiproc) glad_vkCreateDevice, 4, physicalDevice, pCreateInfo, pAllocator, pDevice);
    ret = glad_vkCreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice);
    _post_call_vulkan_callback((void*) &ret, "vkCreateDevice", (GLADapiproc) glad_vkCreateDevice, 4, physicalDevice, pCreateInfo, pAllocator, pDevice);
    return ret;
}
PFN_vkCreateDevice glad_debug_vkCreateDevice = glad_debug_impl_vkCreateDevice;
PFN_vkCreateEvent glad_vkCreateEvent = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateEvent(VkDevice device, const VkEventCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkEvent * pEvent) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateEvent", (GLADapiproc) glad_vkCreateEvent, 4, device, pCreateInfo, pAllocator, pEvent);
    ret = glad_vkCreateEvent(device, pCreateInfo, pAllocator, pEvent);
    _post_call_vulkan_callback((void*) &ret, "vkCreateEvent", (GLADapiproc) glad_vkCreateEvent, 4, device, pCreateInfo, pAllocator, pEvent);
    return ret;
}
PFN_vkCreateEvent glad_debug_vkCreateEvent = glad_debug_impl_vkCreateEvent;
PFN_vkCreateFence glad_vkCreateFence = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateFence(VkDevice device, const VkFenceCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkFence * pFence) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateFence", (GLADapiproc) glad_vkCreateFence, 4, device, pCreateInfo, pAllocator, pFence);
    ret = glad_vkCreateFence(device, pCreateInfo, pAllocator, pFence);
    _post_call_vulkan_callback((void*) &ret, "vkCreateFence", (GLADapiproc) glad_vkCreateFence, 4, device, pCreateInfo, pAllocator, pFence);
    return ret;
}
PFN_vkCreateFence glad_debug_vkCreateFence = glad_debug_impl_vkCreateFence;
PFN_vkCreateFramebuffer glad_vkCreateFramebuffer = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkFramebuffer * pFramebuffer) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateFramebuffer", (GLADapiproc) glad_vkCreateFramebuffer, 4, device, pCreateInfo, pAllocator, pFramebuffer);
    ret = glad_vkCreateFramebuffer(device, pCreateInfo, pAllocator, pFramebuffer);
    _post_call_vulkan_callback((void*) &ret, "vkCreateFramebuffer", (GLADapiproc) glad_vkCreateFramebuffer, 4, device, pCreateInfo, pAllocator, pFramebuffer);
    return ret;
}
PFN_vkCreateFramebuffer glad_debug_vkCreateFramebuffer = glad_debug_impl_vkCreateFramebuffer;
PFN_vkCreateGraphicsPipelines glad_vkCreateGraphicsPipelines = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo * pCreateInfos, const VkAllocationCallbacks * pAllocator, VkPipeline * pPipelines) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateGraphicsPipelines", (GLADapiproc) glad_vkCreateGraphicsPipelines, 6, device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    ret = glad_vkCreateGraphicsPipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    _post_call_vulkan_callback((void*) &ret, "vkCreateGraphicsPipelines", (GLADapiproc) glad_vkCreateGraphicsPipelines, 6, device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
    return ret;
}
PFN_vkCreateGraphicsPipelines glad_debug_vkCreateGraphicsPipelines = glad_debug_impl_vkCreateGraphicsPipelines;
PFN_vkCreateImage glad_vkCreateImage = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateImage(VkDevice device, const VkImageCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkImage * pImage) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateImage", (GLADapiproc) glad_vkCreateImage, 4, device, pCreateInfo, pAllocator, pImage);
    ret = glad_vkCreateImage(device, pCreateInfo, pAllocator, pImage);
    _post_call_vulkan_callback((void*) &ret, "vkCreateImage", (GLADapiproc) glad_vkCreateImage, 4, device, pCreateInfo, pAllocator, pImage);
    return ret;
}
PFN_vkCreateImage glad_debug_vkCreateImage = glad_debug_impl_vkCreateImage;
PFN_vkCreateImageView glad_vkCreateImageView = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateImageView(VkDevice device, const VkImageViewCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkImageView * pView) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateImageView", (GLADapiproc) glad_vkCreateImageView, 4, device, pCreateInfo, pAllocator, pView);
    ret = glad_vkCreateImageView(device, pCreateInfo, pAllocator, pView);
    _post_call_vulkan_callback((void*) &ret, "vkCreateImageView", (GLADapiproc) glad_vkCreateImageView, 4, device, pCreateInfo, pAllocator, pView);
    return ret;
}
PFN_vkCreateImageView glad_debug_vkCreateImageView = glad_debug_impl_vkCreateImageView;
PFN_vkCreateInstance glad_vkCreateInstance = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateInstance(const VkInstanceCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkInstance * pInstance) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateInstance", (GLADapiproc) glad_vkCreateInstance, 3, pCreateInfo, pAllocator, pInstance);
    ret = glad_vkCreateInstance(pCreateInfo, pAllocator, pInstance);
    _post_call_vulkan_callback((void*) &ret, "vkCreateInstance", (GLADapiproc) glad_vkCreateInstance, 3, pCreateInfo, pAllocator, pInstance);
    return ret;
}
PFN_vkCreateInstance glad_debug_vkCreateInstance = glad_debug_impl_vkCreateInstance;
PFN_vkCreatePipelineCache glad_vkCreatePipelineCache = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkPipelineCache * pPipelineCache) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreatePipelineCache", (GLADapiproc) glad_vkCreatePipelineCache, 4, device, pCreateInfo, pAllocator, pPipelineCache);
    ret = glad_vkCreatePipelineCache(device, pCreateInfo, pAllocator, pPipelineCache);
    _post_call_vulkan_callback((void*) &ret, "vkCreatePipelineCache", (GLADapiproc) glad_vkCreatePipelineCache, 4, device, pCreateInfo, pAllocator, pPipelineCache);
    return ret;
}
PFN_vkCreatePipelineCache glad_debug_vkCreatePipelineCache = glad_debug_impl_vkCreatePipelineCache;
PFN_vkCreatePipelineLayout glad_vkCreatePipelineLayout = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkPipelineLayout * pPipelineLayout) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreatePipelineLayout", (GLADapiproc) glad_vkCreatePipelineLayout, 4, device, pCreateInfo, pAllocator, pPipelineLayout);
    ret = glad_vkCreatePipelineLayout(device, pCreateInfo, pAllocator, pPipelineLayout);
    _post_call_vulkan_callback((void*) &ret, "vkCreatePipelineLayout", (GLADapiproc) glad_vkCreatePipelineLayout, 4, device, pCreateInfo, pAllocator, pPipelineLayout);
    return ret;
}
PFN_vkCreatePipelineLayout glad_debug_vkCreatePipelineLayout = glad_debug_impl_vkCreatePipelineLayout;
PFN_vkCreatePrivateDataSlot glad_vkCreatePrivateDataSlot = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreatePrivateDataSlot(VkDevice device, const VkPrivateDataSlotCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkPrivateDataSlot * pPrivateDataSlot) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreatePrivateDataSlot", (GLADapiproc) glad_vkCreatePrivateDataSlot, 4, device, pCreateInfo, pAllocator, pPrivateDataSlot);
    ret = glad_vkCreatePrivateDataSlot(device, pCreateInfo, pAllocator, pPrivateDataSlot);
    _post_call_vulkan_callback((void*) &ret, "vkCreatePrivateDataSlot", (GLADapiproc) glad_vkCreatePrivateDataSlot, 4, device, pCreateInfo, pAllocator, pPrivateDataSlot);
    return ret;
}
PFN_vkCreatePrivateDataSlot glad_debug_vkCreatePrivateDataSlot = glad_debug_impl_vkCreatePrivateDataSlot;
PFN_vkCreatePrivateDataSlotEXT glad_vkCreatePrivateDataSlotEXT = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreatePrivateDataSlotEXT(VkDevice device, const VkPrivateDataSlotCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkPrivateDataSlot * pPrivateDataSlot) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreatePrivateDataSlotEXT", (GLADapiproc) glad_vkCreatePrivateDataSlotEXT, 4, device, pCreateInfo, pAllocator, pPrivateDataSlot);
    ret = glad_vkCreatePrivateDataSlotEXT(device, pCreateInfo, pAllocator, pPrivateDataSlot);
    _post_call_vulkan_callback((void*) &ret, "vkCreatePrivateDataSlotEXT", (GLADapiproc) glad_vkCreatePrivateDataSlotEXT, 4, device, pCreateInfo, pAllocator, pPrivateDataSlot);
    return ret;
}
PFN_vkCreatePrivateDataSlotEXT glad_debug_vkCreatePrivateDataSlotEXT = glad_debug_impl_vkCreatePrivateDataSlotEXT;
PFN_vkCreateQueryPool glad_vkCreateQueryPool = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkQueryPool * pQueryPool) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateQueryPool", (GLADapiproc) glad_vkCreateQueryPool, 4, device, pCreateInfo, pAllocator, pQueryPool);
    ret = glad_vkCreateQueryPool(device, pCreateInfo, pAllocator, pQueryPool);
    _post_call_vulkan_callback((void*) &ret, "vkCreateQueryPool", (GLADapiproc) glad_vkCreateQueryPool, 4, device, pCreateInfo, pAllocator, pQueryPool);
    return ret;
}
PFN_vkCreateQueryPool glad_debug_vkCreateQueryPool = glad_debug_impl_vkCreateQueryPool;
PFN_vkCreateRenderPass glad_vkCreateRenderPass = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateRenderPass(VkDevice device, const VkRenderPassCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkRenderPass * pRenderPass) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateRenderPass", (GLADapiproc) glad_vkCreateRenderPass, 4, device, pCreateInfo, pAllocator, pRenderPass);
    ret = glad_vkCreateRenderPass(device, pCreateInfo, pAllocator, pRenderPass);
    _post_call_vulkan_callback((void*) &ret, "vkCreateRenderPass", (GLADapiproc) glad_vkCreateRenderPass, 4, device, pCreateInfo, pAllocator, pRenderPass);
    return ret;
}
PFN_vkCreateRenderPass glad_debug_vkCreateRenderPass = glad_debug_impl_vkCreateRenderPass;
PFN_vkCreateRenderPass2 glad_vkCreateRenderPass2 = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2 * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkRenderPass * pRenderPass) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateRenderPass2", (GLADapiproc) glad_vkCreateRenderPass2, 4, device, pCreateInfo, pAllocator, pRenderPass);
    ret = glad_vkCreateRenderPass2(device, pCreateInfo, pAllocator, pRenderPass);
    _post_call_vulkan_callback((void*) &ret, "vkCreateRenderPass2", (GLADapiproc) glad_vkCreateRenderPass2, 4, device, pCreateInfo, pAllocator, pRenderPass);
    return ret;
}
PFN_vkCreateRenderPass2 glad_debug_vkCreateRenderPass2 = glad_debug_impl_vkCreateRenderPass2;
PFN_vkCreateRenderPass2KHR glad_vkCreateRenderPass2KHR = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateRenderPass2KHR(VkDevice device, const VkRenderPassCreateInfo2 * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkRenderPass * pRenderPass) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateRenderPass2KHR", (GLADapiproc) glad_vkCreateRenderPass2KHR, 4, device, pCreateInfo, pAllocator, pRenderPass);
    ret = glad_vkCreateRenderPass2KHR(device, pCreateInfo, pAllocator, pRenderPass);
    _post_call_vulkan_callback((void*) &ret, "vkCreateRenderPass2KHR", (GLADapiproc) glad_vkCreateRenderPass2KHR, 4, device, pCreateInfo, pAllocator, pRenderPass);
    return ret;
}
PFN_vkCreateRenderPass2KHR glad_debug_vkCreateRenderPass2KHR = glad_debug_impl_vkCreateRenderPass2KHR;
PFN_vkCreateSampler glad_vkCreateSampler = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateSampler(VkDevice device, const VkSamplerCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSampler * pSampler) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateSampler", (GLADapiproc) glad_vkCreateSampler, 4, device, pCreateInfo, pAllocator, pSampler);
    ret = glad_vkCreateSampler(device, pCreateInfo, pAllocator, pSampler);
    _post_call_vulkan_callback((void*) &ret, "vkCreateSampler", (GLADapiproc) glad_vkCreateSampler, 4, device, pCreateInfo, pAllocator, pSampler);
    return ret;
}
PFN_vkCreateSampler glad_debug_vkCreateSampler = glad_debug_impl_vkCreateSampler;
PFN_vkCreateSamplerYcbcrConversion glad_vkCreateSamplerYcbcrConversion = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSamplerYcbcrConversion * pYcbcrConversion) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateSamplerYcbcrConversion", (GLADapiproc) glad_vkCreateSamplerYcbcrConversion, 4, device, pCreateInfo, pAllocator, pYcbcrConversion);
    ret = glad_vkCreateSamplerYcbcrConversion(device, pCreateInfo, pAllocator, pYcbcrConversion);
    _post_call_vulkan_callback((void*) &ret, "vkCreateSamplerYcbcrConversion", (GLADapiproc) glad_vkCreateSamplerYcbcrConversion, 4, device, pCreateInfo, pAllocator, pYcbcrConversion);
    return ret;
}
PFN_vkCreateSamplerYcbcrConversion glad_debug_vkCreateSamplerYcbcrConversion = glad_debug_impl_vkCreateSamplerYcbcrConversion;
PFN_vkCreateSamplerYcbcrConversionKHR glad_vkCreateSamplerYcbcrConversionKHR = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateSamplerYcbcrConversionKHR(VkDevice device, const VkSamplerYcbcrConversionCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSamplerYcbcrConversion * pYcbcrConversion) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateSamplerYcbcrConversionKHR", (GLADapiproc) glad_vkCreateSamplerYcbcrConversionKHR, 4, device, pCreateInfo, pAllocator, pYcbcrConversion);
    ret = glad_vkCreateSamplerYcbcrConversionKHR(device, pCreateInfo, pAllocator, pYcbcrConversion);
    _post_call_vulkan_callback((void*) &ret, "vkCreateSamplerYcbcrConversionKHR", (GLADapiproc) glad_vkCreateSamplerYcbcrConversionKHR, 4, device, pCreateInfo, pAllocator, pYcbcrConversion);
    return ret;
}
PFN_vkCreateSamplerYcbcrConversionKHR glad_debug_vkCreateSamplerYcbcrConversionKHR = glad_debug_impl_vkCreateSamplerYcbcrConversionKHR;
PFN_vkCreateSemaphore glad_vkCreateSemaphore = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkSemaphore * pSemaphore) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateSemaphore", (GLADapiproc) glad_vkCreateSemaphore, 4, device, pCreateInfo, pAllocator, pSemaphore);
    ret = glad_vkCreateSemaphore(device, pCreateInfo, pAllocator, pSemaphore);
    _post_call_vulkan_callback((void*) &ret, "vkCreateSemaphore", (GLADapiproc) glad_vkCreateSemaphore, 4, device, pCreateInfo, pAllocator, pSemaphore);
    return ret;
}
PFN_vkCreateSemaphore glad_debug_vkCreateSemaphore = glad_debug_impl_vkCreateSemaphore;
PFN_vkCreateShaderModule glad_vkCreateShaderModule = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkShaderModule * pShaderModule) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateShaderModule", (GLADapiproc) glad_vkCreateShaderModule, 4, device, pCreateInfo, pAllocator, pShaderModule);
    ret = glad_vkCreateShaderModule(device, pCreateInfo, pAllocator, pShaderModule);
    _post_call_vulkan_callback((void*) &ret, "vkCreateShaderModule", (GLADapiproc) glad_vkCreateShaderModule, 4, device, pCreateInfo, pAllocator, pShaderModule);
    return ret;
}
PFN_vkCreateShaderModule glad_debug_vkCreateShaderModule = glad_debug_impl_vkCreateShaderModule;
PFN_vkCreateShadersEXT glad_vkCreateShadersEXT = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkCreateShadersEXT(VkDevice device, uint32_t createInfoCount, const VkShaderCreateInfoEXT * pCreateInfos, const VkAllocationCallbacks * pAllocator, VkShaderEXT * pShaders) {
    VkResult ret;
    _pre_call_vulkan_callback("vkCreateShadersEXT", (GLADapiproc) glad_vkCreateShadersEXT, 5, device, createInfoCount, pCreateInfos, pAllocator, pShaders);
    ret = glad_vkCreateShadersEXT(device, createInfoCount, pCreateInfos, pAllocator, pShaders);
    _post_call_vulkan_callback((void*) &ret, "vkCreateShadersEXT", (GLADapiproc) glad_vkCreateShadersEXT, 5, device, createInfoCount, pCreateInfos, pAllocator, pShaders);
    return ret;
}
PFN_vkCreateShadersEXT glad_debug_vkCreateShadersEXT = glad_debug_impl_vkCreateShadersEXT;
PFN_vkDestroyBuffer glad_vkDestroyBuffer = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyBuffer", (GLADapiproc) glad_vkDestroyBuffer, 3, device, buffer, pAllocator);
    glad_vkDestroyBuffer(device, buffer, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyBuffer", (GLADapiproc) glad_vkDestroyBuffer, 3, device, buffer, pAllocator);
    
}
PFN_vkDestroyBuffer glad_debug_vkDestroyBuffer = glad_debug_impl_vkDestroyBuffer;
PFN_vkDestroyBufferView glad_vkDestroyBufferView = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyBufferView", (GLADapiproc) glad_vkDestroyBufferView, 3, device, bufferView, pAllocator);
    glad_vkDestroyBufferView(device, bufferView, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyBufferView", (GLADapiproc) glad_vkDestroyBufferView, 3, device, bufferView, pAllocator);
    
}
PFN_vkDestroyBufferView glad_debug_vkDestroyBufferView = glad_debug_impl_vkDestroyBufferView;
PFN_vkDestroyCommandPool glad_vkDestroyCommandPool = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyCommandPool", (GLADapiproc) glad_vkDestroyCommandPool, 3, device, commandPool, pAllocator);
    glad_vkDestroyCommandPool(device, commandPool, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyCommandPool", (GLADapiproc) glad_vkDestroyCommandPool, 3, device, commandPool, pAllocator);
    
}
PFN_vkDestroyCommandPool glad_debug_vkDestroyCommandPool = glad_debug_impl_vkDestroyCommandPool;
PFN_vkDestroyDescriptorPool glad_vkDestroyDescriptorPool = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyDescriptorPool", (GLADapiproc) glad_vkDestroyDescriptorPool, 3, device, descriptorPool, pAllocator);
    glad_vkDestroyDescriptorPool(device, descriptorPool, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyDescriptorPool", (GLADapiproc) glad_vkDestroyDescriptorPool, 3, device, descriptorPool, pAllocator);
    
}
PFN_vkDestroyDescriptorPool glad_debug_vkDestroyDescriptorPool = glad_debug_impl_vkDestroyDescriptorPool;
PFN_vkDestroyDescriptorSetLayout glad_vkDestroyDescriptorSetLayout = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyDescriptorSetLayout", (GLADapiproc) glad_vkDestroyDescriptorSetLayout, 3, device, descriptorSetLayout, pAllocator);
    glad_vkDestroyDescriptorSetLayout(device, descriptorSetLayout, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyDescriptorSetLayout", (GLADapiproc) glad_vkDestroyDescriptorSetLayout, 3, device, descriptorSetLayout, pAllocator);
    
}
PFN_vkDestroyDescriptorSetLayout glad_debug_vkDestroyDescriptorSetLayout = glad_debug_impl_vkDestroyDescriptorSetLayout;
PFN_vkDestroyDescriptorUpdateTemplate glad_vkDestroyDescriptorUpdateTemplate = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyDescriptorUpdateTemplate", (GLADapiproc) glad_vkDestroyDescriptorUpdateTemplate, 3, device, descriptorUpdateTemplate, pAllocator);
    glad_vkDestroyDescriptorUpdateTemplate(device, descriptorUpdateTemplate, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyDescriptorUpdateTemplate", (GLADapiproc) glad_vkDestroyDescriptorUpdateTemplate, 3, device, descriptorUpdateTemplate, pAllocator);
    
}
PFN_vkDestroyDescriptorUpdateTemplate glad_debug_vkDestroyDescriptorUpdateTemplate = glad_debug_impl_vkDestroyDescriptorUpdateTemplate;
PFN_vkDestroyDescriptorUpdateTemplateKHR glad_vkDestroyDescriptorUpdateTemplateKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyDescriptorUpdateTemplateKHR", (GLADapiproc) glad_vkDestroyDescriptorUpdateTemplateKHR, 3, device, descriptorUpdateTemplate, pAllocator);
    glad_vkDestroyDescriptorUpdateTemplateKHR(device, descriptorUpdateTemplate, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyDescriptorUpdateTemplateKHR", (GLADapiproc) glad_vkDestroyDescriptorUpdateTemplateKHR, 3, device, descriptorUpdateTemplate, pAllocator);
    
}
PFN_vkDestroyDescriptorUpdateTemplateKHR glad_debug_vkDestroyDescriptorUpdateTemplateKHR = glad_debug_impl_vkDestroyDescriptorUpdateTemplateKHR;
PFN_vkDestroyDevice glad_vkDestroyDevice = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyDevice(VkDevice device, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyDevice", (GLADapiproc) glad_vkDestroyDevice, 2, device, pAllocator);
    glad_vkDestroyDevice(device, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyDevice", (GLADapiproc) glad_vkDestroyDevice, 2, device, pAllocator);
    
}
PFN_vkDestroyDevice glad_debug_vkDestroyDevice = glad_debug_impl_vkDestroyDevice;
PFN_vkDestroyEvent glad_vkDestroyEvent = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyEvent", (GLADapiproc) glad_vkDestroyEvent, 3, device, event, pAllocator);
    glad_vkDestroyEvent(device, event, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyEvent", (GLADapiproc) glad_vkDestroyEvent, 3, device, event, pAllocator);
    
}
PFN_vkDestroyEvent glad_debug_vkDestroyEvent = glad_debug_impl_vkDestroyEvent;
PFN_vkDestroyFence glad_vkDestroyFence = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyFence", (GLADapiproc) glad_vkDestroyFence, 3, device, fence, pAllocator);
    glad_vkDestroyFence(device, fence, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyFence", (GLADapiproc) glad_vkDestroyFence, 3, device, fence, pAllocator);
    
}
PFN_vkDestroyFence glad_debug_vkDestroyFence = glad_debug_impl_vkDestroyFence;
PFN_vkDestroyFramebuffer glad_vkDestroyFramebuffer = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyFramebuffer", (GLADapiproc) glad_vkDestroyFramebuffer, 3, device, framebuffer, pAllocator);
    glad_vkDestroyFramebuffer(device, framebuffer, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyFramebuffer", (GLADapiproc) glad_vkDestroyFramebuffer, 3, device, framebuffer, pAllocator);
    
}
PFN_vkDestroyFramebuffer glad_debug_vkDestroyFramebuffer = glad_debug_impl_vkDestroyFramebuffer;
PFN_vkDestroyImage glad_vkDestroyImage = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyImage", (GLADapiproc) glad_vkDestroyImage, 3, device, image, pAllocator);
    glad_vkDestroyImage(device, image, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyImage", (GLADapiproc) glad_vkDestroyImage, 3, device, image, pAllocator);
    
}
PFN_vkDestroyImage glad_debug_vkDestroyImage = glad_debug_impl_vkDestroyImage;
PFN_vkDestroyImageView glad_vkDestroyImageView = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyImageView", (GLADapiproc) glad_vkDestroyImageView, 3, device, imageView, pAllocator);
    glad_vkDestroyImageView(device, imageView, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyImageView", (GLADapiproc) glad_vkDestroyImageView, 3, device, imageView, pAllocator);
    
}
PFN_vkDestroyImageView glad_debug_vkDestroyImageView = glad_debug_impl_vkDestroyImageView;
PFN_vkDestroyInstance glad_vkDestroyInstance = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyInstance", (GLADapiproc) glad_vkDestroyInstance, 2, instance, pAllocator);
    glad_vkDestroyInstance(instance, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyInstance", (GLADapiproc) glad_vkDestroyInstance, 2, instance, pAllocator);
    
}
PFN_vkDestroyInstance glad_debug_vkDestroyInstance = glad_debug_impl_vkDestroyInstance;
PFN_vkDestroyPipeline glad_vkDestroyPipeline = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyPipeline", (GLADapiproc) glad_vkDestroyPipeline, 3, device, pipeline, pAllocator);
    glad_vkDestroyPipeline(device, pipeline, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyPipeline", (GLADapiproc) glad_vkDestroyPipeline, 3, device, pipeline, pAllocator);
    
}
PFN_vkDestroyPipeline glad_debug_vkDestroyPipeline = glad_debug_impl_vkDestroyPipeline;
PFN_vkDestroyPipelineCache glad_vkDestroyPipelineCache = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyPipelineCache", (GLADapiproc) glad_vkDestroyPipelineCache, 3, device, pipelineCache, pAllocator);
    glad_vkDestroyPipelineCache(device, pipelineCache, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyPipelineCache", (GLADapiproc) glad_vkDestroyPipelineCache, 3, device, pipelineCache, pAllocator);
    
}
PFN_vkDestroyPipelineCache glad_debug_vkDestroyPipelineCache = glad_debug_impl_vkDestroyPipelineCache;
PFN_vkDestroyPipelineLayout glad_vkDestroyPipelineLayout = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyPipelineLayout", (GLADapiproc) glad_vkDestroyPipelineLayout, 3, device, pipelineLayout, pAllocator);
    glad_vkDestroyPipelineLayout(device, pipelineLayout, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyPipelineLayout", (GLADapiproc) glad_vkDestroyPipelineLayout, 3, device, pipelineLayout, pAllocator);
    
}
PFN_vkDestroyPipelineLayout glad_debug_vkDestroyPipelineLayout = glad_debug_impl_vkDestroyPipelineLayout;
PFN_vkDestroyPrivateDataSlot glad_vkDestroyPrivateDataSlot = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyPrivateDataSlot(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyPrivateDataSlot", (GLADapiproc) glad_vkDestroyPrivateDataSlot, 3, device, privateDataSlot, pAllocator);
    glad_vkDestroyPrivateDataSlot(device, privateDataSlot, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyPrivateDataSlot", (GLADapiproc) glad_vkDestroyPrivateDataSlot, 3, device, privateDataSlot, pAllocator);
    
}
PFN_vkDestroyPrivateDataSlot glad_debug_vkDestroyPrivateDataSlot = glad_debug_impl_vkDestroyPrivateDataSlot;
PFN_vkDestroyPrivateDataSlotEXT glad_vkDestroyPrivateDataSlotEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyPrivateDataSlotEXT(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyPrivateDataSlotEXT", (GLADapiproc) glad_vkDestroyPrivateDataSlotEXT, 3, device, privateDataSlot, pAllocator);
    glad_vkDestroyPrivateDataSlotEXT(device, privateDataSlot, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyPrivateDataSlotEXT", (GLADapiproc) glad_vkDestroyPrivateDataSlotEXT, 3, device, privateDataSlot, pAllocator);
    
}
PFN_vkDestroyPrivateDataSlotEXT glad_debug_vkDestroyPrivateDataSlotEXT = glad_debug_impl_vkDestroyPrivateDataSlotEXT;
PFN_vkDestroyQueryPool glad_vkDestroyQueryPool = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyQueryPool", (GLADapiproc) glad_vkDestroyQueryPool, 3, device, queryPool, pAllocator);
    glad_vkDestroyQueryPool(device, queryPool, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyQueryPool", (GLADapiproc) glad_vkDestroyQueryPool, 3, device, queryPool, pAllocator);
    
}
PFN_vkDestroyQueryPool glad_debug_vkDestroyQueryPool = glad_debug_impl_vkDestroyQueryPool;
PFN_vkDestroyRenderPass glad_vkDestroyRenderPass = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyRenderPass", (GLADapiproc) glad_vkDestroyRenderPass, 3, device, renderPass, pAllocator);
    glad_vkDestroyRenderPass(device, renderPass, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyRenderPass", (GLADapiproc) glad_vkDestroyRenderPass, 3, device, renderPass, pAllocator);
    
}
PFN_vkDestroyRenderPass glad_debug_vkDestroyRenderPass = glad_debug_impl_vkDestroyRenderPass;
PFN_vkDestroySampler glad_vkDestroySampler = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroySampler", (GLADapiproc) glad_vkDestroySampler, 3, device, sampler, pAllocator);
    glad_vkDestroySampler(device, sampler, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroySampler", (GLADapiproc) glad_vkDestroySampler, 3, device, sampler, pAllocator);
    
}
PFN_vkDestroySampler glad_debug_vkDestroySampler = glad_debug_impl_vkDestroySampler;
PFN_vkDestroySamplerYcbcrConversion glad_vkDestroySamplerYcbcrConversion = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroySamplerYcbcrConversion", (GLADapiproc) glad_vkDestroySamplerYcbcrConversion, 3, device, ycbcrConversion, pAllocator);
    glad_vkDestroySamplerYcbcrConversion(device, ycbcrConversion, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroySamplerYcbcrConversion", (GLADapiproc) glad_vkDestroySamplerYcbcrConversion, 3, device, ycbcrConversion, pAllocator);
    
}
PFN_vkDestroySamplerYcbcrConversion glad_debug_vkDestroySamplerYcbcrConversion = glad_debug_impl_vkDestroySamplerYcbcrConversion;
PFN_vkDestroySamplerYcbcrConversionKHR glad_vkDestroySamplerYcbcrConversionKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroySamplerYcbcrConversionKHR", (GLADapiproc) glad_vkDestroySamplerYcbcrConversionKHR, 3, device, ycbcrConversion, pAllocator);
    glad_vkDestroySamplerYcbcrConversionKHR(device, ycbcrConversion, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroySamplerYcbcrConversionKHR", (GLADapiproc) glad_vkDestroySamplerYcbcrConversionKHR, 3, device, ycbcrConversion, pAllocator);
    
}
PFN_vkDestroySamplerYcbcrConversionKHR glad_debug_vkDestroySamplerYcbcrConversionKHR = glad_debug_impl_vkDestroySamplerYcbcrConversionKHR;
PFN_vkDestroySemaphore glad_vkDestroySemaphore = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroySemaphore", (GLADapiproc) glad_vkDestroySemaphore, 3, device, semaphore, pAllocator);
    glad_vkDestroySemaphore(device, semaphore, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroySemaphore", (GLADapiproc) glad_vkDestroySemaphore, 3, device, semaphore, pAllocator);
    
}
PFN_vkDestroySemaphore glad_debug_vkDestroySemaphore = glad_debug_impl_vkDestroySemaphore;
PFN_vkDestroyShaderEXT glad_vkDestroyShaderEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyShaderEXT(VkDevice device, VkShaderEXT shader, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyShaderEXT", (GLADapiproc) glad_vkDestroyShaderEXT, 3, device, shader, pAllocator);
    glad_vkDestroyShaderEXT(device, shader, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyShaderEXT", (GLADapiproc) glad_vkDestroyShaderEXT, 3, device, shader, pAllocator);
    
}
PFN_vkDestroyShaderEXT glad_debug_vkDestroyShaderEXT = glad_debug_impl_vkDestroyShaderEXT;
PFN_vkDestroyShaderModule glad_vkDestroyShaderModule = NULL;
static void GLAD_API_PTR glad_debug_impl_vkDestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkDestroyShaderModule", (GLADapiproc) glad_vkDestroyShaderModule, 3, device, shaderModule, pAllocator);
    glad_vkDestroyShaderModule(device, shaderModule, pAllocator);
    _post_call_vulkan_callback(NULL, "vkDestroyShaderModule", (GLADapiproc) glad_vkDestroyShaderModule, 3, device, shaderModule, pAllocator);
    
}
PFN_vkDestroyShaderModule glad_debug_vkDestroyShaderModule = glad_debug_impl_vkDestroyShaderModule;
PFN_vkDeviceWaitIdle glad_vkDeviceWaitIdle = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkDeviceWaitIdle(VkDevice device) {
    VkResult ret;
    _pre_call_vulkan_callback("vkDeviceWaitIdle", (GLADapiproc) glad_vkDeviceWaitIdle, 1, device);
    ret = glad_vkDeviceWaitIdle(device);
    _post_call_vulkan_callback((void*) &ret, "vkDeviceWaitIdle", (GLADapiproc) glad_vkDeviceWaitIdle, 1, device);
    return ret;
}
PFN_vkDeviceWaitIdle glad_debug_vkDeviceWaitIdle = glad_debug_impl_vkDeviceWaitIdle;
PFN_vkEndCommandBuffer glad_vkEndCommandBuffer = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkEndCommandBuffer(VkCommandBuffer commandBuffer) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEndCommandBuffer", (GLADapiproc) glad_vkEndCommandBuffer, 1, commandBuffer);
    ret = glad_vkEndCommandBuffer(commandBuffer);
    _post_call_vulkan_callback((void*) &ret, "vkEndCommandBuffer", (GLADapiproc) glad_vkEndCommandBuffer, 1, commandBuffer);
    return ret;
}
PFN_vkEndCommandBuffer glad_debug_vkEndCommandBuffer = glad_debug_impl_vkEndCommandBuffer;
PFN_vkEnumerateDeviceExtensionProperties glad_vkEnumerateDeviceExtensionProperties = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const char * pLayerName, uint32_t * pPropertyCount, VkExtensionProperties * pProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEnumerateDeviceExtensionProperties", (GLADapiproc) glad_vkEnumerateDeviceExtensionProperties, 4, physicalDevice, pLayerName, pPropertyCount, pProperties);
    ret = glad_vkEnumerateDeviceExtensionProperties(physicalDevice, pLayerName, pPropertyCount, pProperties);
    _post_call_vulkan_callback((void*) &ret, "vkEnumerateDeviceExtensionProperties", (GLADapiproc) glad_vkEnumerateDeviceExtensionProperties, 4, physicalDevice, pLayerName, pPropertyCount, pProperties);
    return ret;
}
PFN_vkEnumerateDeviceExtensionProperties glad_debug_vkEnumerateDeviceExtensionProperties = glad_debug_impl_vkEnumerateDeviceExtensionProperties;
PFN_vkEnumerateDeviceLayerProperties glad_vkEnumerateDeviceLayerProperties = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkEnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t * pPropertyCount, VkLayerProperties * pProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEnumerateDeviceLayerProperties", (GLADapiproc) glad_vkEnumerateDeviceLayerProperties, 3, physicalDevice, pPropertyCount, pProperties);
    ret = glad_vkEnumerateDeviceLayerProperties(physicalDevice, pPropertyCount, pProperties);
    _post_call_vulkan_callback((void*) &ret, "vkEnumerateDeviceLayerProperties", (GLADapiproc) glad_vkEnumerateDeviceLayerProperties, 3, physicalDevice, pPropertyCount, pProperties);
    return ret;
}
PFN_vkEnumerateDeviceLayerProperties glad_debug_vkEnumerateDeviceLayerProperties = glad_debug_impl_vkEnumerateDeviceLayerProperties;
PFN_vkEnumerateInstanceExtensionProperties glad_vkEnumerateInstanceExtensionProperties = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkEnumerateInstanceExtensionProperties(const char * pLayerName, uint32_t * pPropertyCount, VkExtensionProperties * pProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEnumerateInstanceExtensionProperties", (GLADapiproc) glad_vkEnumerateInstanceExtensionProperties, 3, pLayerName, pPropertyCount, pProperties);
    ret = glad_vkEnumerateInstanceExtensionProperties(pLayerName, pPropertyCount, pProperties);
    _post_call_vulkan_callback((void*) &ret, "vkEnumerateInstanceExtensionProperties", (GLADapiproc) glad_vkEnumerateInstanceExtensionProperties, 3, pLayerName, pPropertyCount, pProperties);
    return ret;
}
PFN_vkEnumerateInstanceExtensionProperties glad_debug_vkEnumerateInstanceExtensionProperties = glad_debug_impl_vkEnumerateInstanceExtensionProperties;
PFN_vkEnumerateInstanceLayerProperties glad_vkEnumerateInstanceLayerProperties = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkEnumerateInstanceLayerProperties(uint32_t * pPropertyCount, VkLayerProperties * pProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEnumerateInstanceLayerProperties", (GLADapiproc) glad_vkEnumerateInstanceLayerProperties, 2, pPropertyCount, pProperties);
    ret = glad_vkEnumerateInstanceLayerProperties(pPropertyCount, pProperties);
    _post_call_vulkan_callback((void*) &ret, "vkEnumerateInstanceLayerProperties", (GLADapiproc) glad_vkEnumerateInstanceLayerProperties, 2, pPropertyCount, pProperties);
    return ret;
}
PFN_vkEnumerateInstanceLayerProperties glad_debug_vkEnumerateInstanceLayerProperties = glad_debug_impl_vkEnumerateInstanceLayerProperties;
PFN_vkEnumerateInstanceVersion glad_vkEnumerateInstanceVersion = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkEnumerateInstanceVersion(uint32_t * pApiVersion) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEnumerateInstanceVersion", (GLADapiproc) glad_vkEnumerateInstanceVersion, 1, pApiVersion);
    ret = glad_vkEnumerateInstanceVersion(pApiVersion);
    _post_call_vulkan_callback((void*) &ret, "vkEnumerateInstanceVersion", (GLADapiproc) glad_vkEnumerateInstanceVersion, 1, pApiVersion);
    return ret;
}
PFN_vkEnumerateInstanceVersion glad_debug_vkEnumerateInstanceVersion = glad_debug_impl_vkEnumerateInstanceVersion;
PFN_vkEnumeratePhysicalDeviceGroups glad_vkEnumeratePhysicalDeviceGroups = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkEnumeratePhysicalDeviceGroups(VkInstance instance, uint32_t * pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties * pPhysicalDeviceGroupProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEnumeratePhysicalDeviceGroups", (GLADapiproc) glad_vkEnumeratePhysicalDeviceGroups, 3, instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
    ret = glad_vkEnumeratePhysicalDeviceGroups(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
    _post_call_vulkan_callback((void*) &ret, "vkEnumeratePhysicalDeviceGroups", (GLADapiproc) glad_vkEnumeratePhysicalDeviceGroups, 3, instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
    return ret;
}
PFN_vkEnumeratePhysicalDeviceGroups glad_debug_vkEnumeratePhysicalDeviceGroups = glad_debug_impl_vkEnumeratePhysicalDeviceGroups;
PFN_vkEnumeratePhysicalDeviceGroupsKHR glad_vkEnumeratePhysicalDeviceGroupsKHR = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkEnumeratePhysicalDeviceGroupsKHR(VkInstance instance, uint32_t * pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties * pPhysicalDeviceGroupProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEnumeratePhysicalDeviceGroupsKHR", (GLADapiproc) glad_vkEnumeratePhysicalDeviceGroupsKHR, 3, instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
    ret = glad_vkEnumeratePhysicalDeviceGroupsKHR(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
    _post_call_vulkan_callback((void*) &ret, "vkEnumeratePhysicalDeviceGroupsKHR", (GLADapiproc) glad_vkEnumeratePhysicalDeviceGroupsKHR, 3, instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
    return ret;
}
PFN_vkEnumeratePhysicalDeviceGroupsKHR glad_debug_vkEnumeratePhysicalDeviceGroupsKHR = glad_debug_impl_vkEnumeratePhysicalDeviceGroupsKHR;
PFN_vkEnumeratePhysicalDevices glad_vkEnumeratePhysicalDevices = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkEnumeratePhysicalDevices(VkInstance instance, uint32_t * pPhysicalDeviceCount, VkPhysicalDevice * pPhysicalDevices) {
    VkResult ret;
    _pre_call_vulkan_callback("vkEnumeratePhysicalDevices", (GLADapiproc) glad_vkEnumeratePhysicalDevices, 3, instance, pPhysicalDeviceCount, pPhysicalDevices);
    ret = glad_vkEnumeratePhysicalDevices(instance, pPhysicalDeviceCount, pPhysicalDevices);
    _post_call_vulkan_callback((void*) &ret, "vkEnumeratePhysicalDevices", (GLADapiproc) glad_vkEnumeratePhysicalDevices, 3, instance, pPhysicalDeviceCount, pPhysicalDevices);
    return ret;
}
PFN_vkEnumeratePhysicalDevices glad_debug_vkEnumeratePhysicalDevices = glad_debug_impl_vkEnumeratePhysicalDevices;
PFN_vkFlushMappedMemoryRanges glad_vkFlushMappedMemoryRanges = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange * pMemoryRanges) {
    VkResult ret;
    _pre_call_vulkan_callback("vkFlushMappedMemoryRanges", (GLADapiproc) glad_vkFlushMappedMemoryRanges, 3, device, memoryRangeCount, pMemoryRanges);
    ret = glad_vkFlushMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
    _post_call_vulkan_callback((void*) &ret, "vkFlushMappedMemoryRanges", (GLADapiproc) glad_vkFlushMappedMemoryRanges, 3, device, memoryRangeCount, pMemoryRanges);
    return ret;
}
PFN_vkFlushMappedMemoryRanges glad_debug_vkFlushMappedMemoryRanges = glad_debug_impl_vkFlushMappedMemoryRanges;
PFN_vkFreeCommandBuffers glad_vkFreeCommandBuffers = NULL;
static void GLAD_API_PTR glad_debug_impl_vkFreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer * pCommandBuffers) {
    _pre_call_vulkan_callback("vkFreeCommandBuffers", (GLADapiproc) glad_vkFreeCommandBuffers, 4, device, commandPool, commandBufferCount, pCommandBuffers);
    glad_vkFreeCommandBuffers(device, commandPool, commandBufferCount, pCommandBuffers);
    _post_call_vulkan_callback(NULL, "vkFreeCommandBuffers", (GLADapiproc) glad_vkFreeCommandBuffers, 4, device, commandPool, commandBufferCount, pCommandBuffers);
    
}
PFN_vkFreeCommandBuffers glad_debug_vkFreeCommandBuffers = glad_debug_impl_vkFreeCommandBuffers;
PFN_vkFreeDescriptorSets glad_vkFreeDescriptorSets = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkFreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet * pDescriptorSets) {
    VkResult ret;
    _pre_call_vulkan_callback("vkFreeDescriptorSets", (GLADapiproc) glad_vkFreeDescriptorSets, 4, device, descriptorPool, descriptorSetCount, pDescriptorSets);
    ret = glad_vkFreeDescriptorSets(device, descriptorPool, descriptorSetCount, pDescriptorSets);
    _post_call_vulkan_callback((void*) &ret, "vkFreeDescriptorSets", (GLADapiproc) glad_vkFreeDescriptorSets, 4, device, descriptorPool, descriptorSetCount, pDescriptorSets);
    return ret;
}
PFN_vkFreeDescriptorSets glad_debug_vkFreeDescriptorSets = glad_debug_impl_vkFreeDescriptorSets;
PFN_vkFreeMemory glad_vkFreeMemory = NULL;
static void GLAD_API_PTR glad_debug_impl_vkFreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks * pAllocator) {
    _pre_call_vulkan_callback("vkFreeMemory", (GLADapiproc) glad_vkFreeMemory, 3, device, memory, pAllocator);
    glad_vkFreeMemory(device, memory, pAllocator);
    _post_call_vulkan_callback(NULL, "vkFreeMemory", (GLADapiproc) glad_vkFreeMemory, 3, device, memory, pAllocator);
    
}
PFN_vkFreeMemory glad_debug_vkFreeMemory = glad_debug_impl_vkFreeMemory;
PFN_vkGetBufferDeviceAddress glad_vkGetBufferDeviceAddress = NULL;
static VkDeviceAddress GLAD_API_PTR glad_debug_impl_vkGetBufferDeviceAddress(VkDevice device, const VkBufferDeviceAddressInfo * pInfo) {
    VkDeviceAddress ret;
    _pre_call_vulkan_callback("vkGetBufferDeviceAddress", (GLADapiproc) glad_vkGetBufferDeviceAddress, 2, device, pInfo);
    ret = glad_vkGetBufferDeviceAddress(device, pInfo);
    _post_call_vulkan_callback((void*) &ret, "vkGetBufferDeviceAddress", (GLADapiproc) glad_vkGetBufferDeviceAddress, 2, device, pInfo);
    return ret;
}
PFN_vkGetBufferDeviceAddress glad_debug_vkGetBufferDeviceAddress = glad_debug_impl_vkGetBufferDeviceAddress;
PFN_vkGetBufferDeviceAddressEXT glad_vkGetBufferDeviceAddressEXT = NULL;
static VkDeviceAddress GLAD_API_PTR glad_debug_impl_vkGetBufferDeviceAddressEXT(VkDevice device, const VkBufferDeviceAddressInfo * pInfo) {
    VkDeviceAddress ret;
    _pre_call_vulkan_callback("vkGetBufferDeviceAddressEXT", (GLADapiproc) glad_vkGetBufferDeviceAddressEXT, 2, device, pInfo);
    ret = glad_vkGetBufferDeviceAddressEXT(device, pInfo);
    _post_call_vulkan_callback((void*) &ret, "vkGetBufferDeviceAddressEXT", (GLADapiproc) glad_vkGetBufferDeviceAddressEXT, 2, device, pInfo);
    return ret;
}
PFN_vkGetBufferDeviceAddressEXT glad_debug_vkGetBufferDeviceAddressEXT = glad_debug_impl_vkGetBufferDeviceAddressEXT;
PFN_vkGetBufferDeviceAddressKHR glad_vkGetBufferDeviceAddressKHR = NULL;
static VkDeviceAddress GLAD_API_PTR glad_debug_impl_vkGetBufferDeviceAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo * pInfo) {
    VkDeviceAddress ret;
    _pre_call_vulkan_callback("vkGetBufferDeviceAddressKHR", (GLADapiproc) glad_vkGetBufferDeviceAddressKHR, 2, device, pInfo);
    ret = glad_vkGetBufferDeviceAddressKHR(device, pInfo);
    _post_call_vulkan_callback((void*) &ret, "vkGetBufferDeviceAddressKHR", (GLADapiproc) glad_vkGetBufferDeviceAddressKHR, 2, device, pInfo);
    return ret;
}
PFN_vkGetBufferDeviceAddressKHR glad_debug_vkGetBufferDeviceAddressKHR = glad_debug_impl_vkGetBufferDeviceAddressKHR;
PFN_vkGetBufferMemoryRequirements glad_vkGetBufferMemoryRequirements = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements * pMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetBufferMemoryRequirements", (GLADapiproc) glad_vkGetBufferMemoryRequirements, 3, device, buffer, pMemoryRequirements);
    glad_vkGetBufferMemoryRequirements(device, buffer, pMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetBufferMemoryRequirements", (GLADapiproc) glad_vkGetBufferMemoryRequirements, 3, device, buffer, pMemoryRequirements);
    
}
PFN_vkGetBufferMemoryRequirements glad_debug_vkGetBufferMemoryRequirements = glad_debug_impl_vkGetBufferMemoryRequirements;
PFN_vkGetBufferMemoryRequirements2 glad_vkGetBufferMemoryRequirements2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2 * pInfo, VkMemoryRequirements2 * pMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetBufferMemoryRequirements2", (GLADapiproc) glad_vkGetBufferMemoryRequirements2, 3, device, pInfo, pMemoryRequirements);
    glad_vkGetBufferMemoryRequirements2(device, pInfo, pMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetBufferMemoryRequirements2", (GLADapiproc) glad_vkGetBufferMemoryRequirements2, 3, device, pInfo, pMemoryRequirements);
    
}
PFN_vkGetBufferMemoryRequirements2 glad_debug_vkGetBufferMemoryRequirements2 = glad_debug_impl_vkGetBufferMemoryRequirements2;
PFN_vkGetBufferMemoryRequirements2KHR glad_vkGetBufferMemoryRequirements2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetBufferMemoryRequirements2KHR(VkDevice device, const VkBufferMemoryRequirementsInfo2 * pInfo, VkMemoryRequirements2 * pMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetBufferMemoryRequirements2KHR", (GLADapiproc) glad_vkGetBufferMemoryRequirements2KHR, 3, device, pInfo, pMemoryRequirements);
    glad_vkGetBufferMemoryRequirements2KHR(device, pInfo, pMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetBufferMemoryRequirements2KHR", (GLADapiproc) glad_vkGetBufferMemoryRequirements2KHR, 3, device, pInfo, pMemoryRequirements);
    
}
PFN_vkGetBufferMemoryRequirements2KHR glad_debug_vkGetBufferMemoryRequirements2KHR = glad_debug_impl_vkGetBufferMemoryRequirements2KHR;
PFN_vkGetBufferOpaqueCaptureAddress glad_vkGetBufferOpaqueCaptureAddress = NULL;
static uint64_t GLAD_API_PTR glad_debug_impl_vkGetBufferOpaqueCaptureAddress(VkDevice device, const VkBufferDeviceAddressInfo * pInfo) {
    uint64_t ret;
    _pre_call_vulkan_callback("vkGetBufferOpaqueCaptureAddress", (GLADapiproc) glad_vkGetBufferOpaqueCaptureAddress, 2, device, pInfo);
    ret = glad_vkGetBufferOpaqueCaptureAddress(device, pInfo);
    _post_call_vulkan_callback((void*) &ret, "vkGetBufferOpaqueCaptureAddress", (GLADapiproc) glad_vkGetBufferOpaqueCaptureAddress, 2, device, pInfo);
    return ret;
}
PFN_vkGetBufferOpaqueCaptureAddress glad_debug_vkGetBufferOpaqueCaptureAddress = glad_debug_impl_vkGetBufferOpaqueCaptureAddress;
PFN_vkGetBufferOpaqueCaptureAddressKHR glad_vkGetBufferOpaqueCaptureAddressKHR = NULL;
static uint64_t GLAD_API_PTR glad_debug_impl_vkGetBufferOpaqueCaptureAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo * pInfo) {
    uint64_t ret;
    _pre_call_vulkan_callback("vkGetBufferOpaqueCaptureAddressKHR", (GLADapiproc) glad_vkGetBufferOpaqueCaptureAddressKHR, 2, device, pInfo);
    ret = glad_vkGetBufferOpaqueCaptureAddressKHR(device, pInfo);
    _post_call_vulkan_callback((void*) &ret, "vkGetBufferOpaqueCaptureAddressKHR", (GLADapiproc) glad_vkGetBufferOpaqueCaptureAddressKHR, 2, device, pInfo);
    return ret;
}
PFN_vkGetBufferOpaqueCaptureAddressKHR glad_debug_vkGetBufferOpaqueCaptureAddressKHR = glad_debug_impl_vkGetBufferOpaqueCaptureAddressKHR;
PFN_vkGetDescriptorSetLayoutSupport glad_vkGetDescriptorSetLayoutSupport = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetDescriptorSetLayoutSupport(VkDevice device, const VkDescriptorSetLayoutCreateInfo * pCreateInfo, VkDescriptorSetLayoutSupport * pSupport) {
    _pre_call_vulkan_callback("vkGetDescriptorSetLayoutSupport", (GLADapiproc) glad_vkGetDescriptorSetLayoutSupport, 3, device, pCreateInfo, pSupport);
    glad_vkGetDescriptorSetLayoutSupport(device, pCreateInfo, pSupport);
    _post_call_vulkan_callback(NULL, "vkGetDescriptorSetLayoutSupport", (GLADapiproc) glad_vkGetDescriptorSetLayoutSupport, 3, device, pCreateInfo, pSupport);
    
}
PFN_vkGetDescriptorSetLayoutSupport glad_debug_vkGetDescriptorSetLayoutSupport = glad_debug_impl_vkGetDescriptorSetLayoutSupport;
PFN_vkGetDescriptorSetLayoutSupportKHR glad_vkGetDescriptorSetLayoutSupportKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetDescriptorSetLayoutSupportKHR(VkDevice device, const VkDescriptorSetLayoutCreateInfo * pCreateInfo, VkDescriptorSetLayoutSupport * pSupport) {
    _pre_call_vulkan_callback("vkGetDescriptorSetLayoutSupportKHR", (GLADapiproc) glad_vkGetDescriptorSetLayoutSupportKHR, 3, device, pCreateInfo, pSupport);
    glad_vkGetDescriptorSetLayoutSupportKHR(device, pCreateInfo, pSupport);
    _post_call_vulkan_callback(NULL, "vkGetDescriptorSetLayoutSupportKHR", (GLADapiproc) glad_vkGetDescriptorSetLayoutSupportKHR, 3, device, pCreateInfo, pSupport);
    
}
PFN_vkGetDescriptorSetLayoutSupportKHR glad_debug_vkGetDescriptorSetLayoutSupportKHR = glad_debug_impl_vkGetDescriptorSetLayoutSupportKHR;
PFN_vkGetDeviceBufferMemoryRequirements glad_vkGetDeviceBufferMemoryRequirements = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceBufferMemoryRequirements(VkDevice device, const VkDeviceBufferMemoryRequirements * pInfo, VkMemoryRequirements2 * pMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetDeviceBufferMemoryRequirements", (GLADapiproc) glad_vkGetDeviceBufferMemoryRequirements, 3, device, pInfo, pMemoryRequirements);
    glad_vkGetDeviceBufferMemoryRequirements(device, pInfo, pMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetDeviceBufferMemoryRequirements", (GLADapiproc) glad_vkGetDeviceBufferMemoryRequirements, 3, device, pInfo, pMemoryRequirements);
    
}
PFN_vkGetDeviceBufferMemoryRequirements glad_debug_vkGetDeviceBufferMemoryRequirements = glad_debug_impl_vkGetDeviceBufferMemoryRequirements;
PFN_vkGetDeviceBufferMemoryRequirementsKHR glad_vkGetDeviceBufferMemoryRequirementsKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceBufferMemoryRequirementsKHR(VkDevice device, const VkDeviceBufferMemoryRequirements * pInfo, VkMemoryRequirements2 * pMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetDeviceBufferMemoryRequirementsKHR", (GLADapiproc) glad_vkGetDeviceBufferMemoryRequirementsKHR, 3, device, pInfo, pMemoryRequirements);
    glad_vkGetDeviceBufferMemoryRequirementsKHR(device, pInfo, pMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetDeviceBufferMemoryRequirementsKHR", (GLADapiproc) glad_vkGetDeviceBufferMemoryRequirementsKHR, 3, device, pInfo, pMemoryRequirements);
    
}
PFN_vkGetDeviceBufferMemoryRequirementsKHR glad_debug_vkGetDeviceBufferMemoryRequirementsKHR = glad_debug_impl_vkGetDeviceBufferMemoryRequirementsKHR;
PFN_vkGetDeviceGroupPeerMemoryFeatures glad_vkGetDeviceGroupPeerMemoryFeatures = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags * pPeerMemoryFeatures) {
    _pre_call_vulkan_callback("vkGetDeviceGroupPeerMemoryFeatures", (GLADapiproc) glad_vkGetDeviceGroupPeerMemoryFeatures, 5, device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    glad_vkGetDeviceGroupPeerMemoryFeatures(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    _post_call_vulkan_callback(NULL, "vkGetDeviceGroupPeerMemoryFeatures", (GLADapiproc) glad_vkGetDeviceGroupPeerMemoryFeatures, 5, device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    
}
PFN_vkGetDeviceGroupPeerMemoryFeatures glad_debug_vkGetDeviceGroupPeerMemoryFeatures = glad_debug_impl_vkGetDeviceGroupPeerMemoryFeatures;
PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR glad_vkGetDeviceGroupPeerMemoryFeaturesKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags * pPeerMemoryFeatures) {
    _pre_call_vulkan_callback("vkGetDeviceGroupPeerMemoryFeaturesKHR", (GLADapiproc) glad_vkGetDeviceGroupPeerMemoryFeaturesKHR, 5, device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    glad_vkGetDeviceGroupPeerMemoryFeaturesKHR(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    _post_call_vulkan_callback(NULL, "vkGetDeviceGroupPeerMemoryFeaturesKHR", (GLADapiproc) glad_vkGetDeviceGroupPeerMemoryFeaturesKHR, 5, device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
    
}
PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR glad_debug_vkGetDeviceGroupPeerMemoryFeaturesKHR = glad_debug_impl_vkGetDeviceGroupPeerMemoryFeaturesKHR;
PFN_vkGetDeviceGroupPresentCapabilitiesKHR glad_vkGetDeviceGroupPresentCapabilitiesKHR = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR * pDeviceGroupPresentCapabilities) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetDeviceGroupPresentCapabilitiesKHR", (GLADapiproc) glad_vkGetDeviceGroupPresentCapabilitiesKHR, 2, device, pDeviceGroupPresentCapabilities);
    ret = glad_vkGetDeviceGroupPresentCapabilitiesKHR(device, pDeviceGroupPresentCapabilities);
    _post_call_vulkan_callback((void*) &ret, "vkGetDeviceGroupPresentCapabilitiesKHR", (GLADapiproc) glad_vkGetDeviceGroupPresentCapabilitiesKHR, 2, device, pDeviceGroupPresentCapabilities);
    return ret;
}
PFN_vkGetDeviceGroupPresentCapabilitiesKHR glad_debug_vkGetDeviceGroupPresentCapabilitiesKHR = glad_debug_impl_vkGetDeviceGroupPresentCapabilitiesKHR;
PFN_vkGetDeviceGroupSurfacePresentModesKHR glad_vkGetDeviceGroupSurfacePresentModesKHR = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR * pModes) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetDeviceGroupSurfacePresentModesKHR", (GLADapiproc) glad_vkGetDeviceGroupSurfacePresentModesKHR, 3, device, surface, pModes);
    ret = glad_vkGetDeviceGroupSurfacePresentModesKHR(device, surface, pModes);
    _post_call_vulkan_callback((void*) &ret, "vkGetDeviceGroupSurfacePresentModesKHR", (GLADapiproc) glad_vkGetDeviceGroupSurfacePresentModesKHR, 3, device, surface, pModes);
    return ret;
}
PFN_vkGetDeviceGroupSurfacePresentModesKHR glad_debug_vkGetDeviceGroupSurfacePresentModesKHR = glad_debug_impl_vkGetDeviceGroupSurfacePresentModesKHR;
PFN_vkGetDeviceImageMemoryRequirements glad_vkGetDeviceImageMemoryRequirements = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceImageMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements * pInfo, VkMemoryRequirements2 * pMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetDeviceImageMemoryRequirements", (GLADapiproc) glad_vkGetDeviceImageMemoryRequirements, 3, device, pInfo, pMemoryRequirements);
    glad_vkGetDeviceImageMemoryRequirements(device, pInfo, pMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetDeviceImageMemoryRequirements", (GLADapiproc) glad_vkGetDeviceImageMemoryRequirements, 3, device, pInfo, pMemoryRequirements);
    
}
PFN_vkGetDeviceImageMemoryRequirements glad_debug_vkGetDeviceImageMemoryRequirements = glad_debug_impl_vkGetDeviceImageMemoryRequirements;
PFN_vkGetDeviceImageMemoryRequirementsKHR glad_vkGetDeviceImageMemoryRequirementsKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceImageMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements * pInfo, VkMemoryRequirements2 * pMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetDeviceImageMemoryRequirementsKHR", (GLADapiproc) glad_vkGetDeviceImageMemoryRequirementsKHR, 3, device, pInfo, pMemoryRequirements);
    glad_vkGetDeviceImageMemoryRequirementsKHR(device, pInfo, pMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetDeviceImageMemoryRequirementsKHR", (GLADapiproc) glad_vkGetDeviceImageMemoryRequirementsKHR, 3, device, pInfo, pMemoryRequirements);
    
}
PFN_vkGetDeviceImageMemoryRequirementsKHR glad_debug_vkGetDeviceImageMemoryRequirementsKHR = glad_debug_impl_vkGetDeviceImageMemoryRequirementsKHR;
PFN_vkGetDeviceImageSparseMemoryRequirements glad_vkGetDeviceImageSparseMemoryRequirements = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceImageSparseMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements * pInfo, uint32_t * pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2 * pSparseMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetDeviceImageSparseMemoryRequirements", (GLADapiproc) glad_vkGetDeviceImageSparseMemoryRequirements, 4, device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    glad_vkGetDeviceImageSparseMemoryRequirements(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetDeviceImageSparseMemoryRequirements", (GLADapiproc) glad_vkGetDeviceImageSparseMemoryRequirements, 4, device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    
}
PFN_vkGetDeviceImageSparseMemoryRequirements glad_debug_vkGetDeviceImageSparseMemoryRequirements = glad_debug_impl_vkGetDeviceImageSparseMemoryRequirements;
PFN_vkGetDeviceImageSparseMemoryRequirementsKHR glad_vkGetDeviceImageSparseMemoryRequirementsKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceImageSparseMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements * pInfo, uint32_t * pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2 * pSparseMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetDeviceImageSparseMemoryRequirementsKHR", (GLADapiproc) glad_vkGetDeviceImageSparseMemoryRequirementsKHR, 4, device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    glad_vkGetDeviceImageSparseMemoryRequirementsKHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetDeviceImageSparseMemoryRequirementsKHR", (GLADapiproc) glad_vkGetDeviceImageSparseMemoryRequirementsKHR, 4, device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    
}
PFN_vkGetDeviceImageSparseMemoryRequirementsKHR glad_debug_vkGetDeviceImageSparseMemoryRequirementsKHR = glad_debug_impl_vkGetDeviceImageSparseMemoryRequirementsKHR;
PFN_vkGetDeviceImageSubresourceLayout glad_vkGetDeviceImageSubresourceLayout = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceImageSubresourceLayout(VkDevice device, const VkDeviceImageSubresourceInfo * pInfo, VkSubresourceLayout2 * pLayout) {
    _pre_call_vulkan_callback("vkGetDeviceImageSubresourceLayout", (GLADapiproc) glad_vkGetDeviceImageSubresourceLayout, 3, device, pInfo, pLayout);
    glad_vkGetDeviceImageSubresourceLayout(device, pInfo, pLayout);
    _post_call_vulkan_callback(NULL, "vkGetDeviceImageSubresourceLayout", (GLADapiproc) glad_vkGetDeviceImageSubresourceLayout, 3, device, pInfo, pLayout);
    
}
PFN_vkGetDeviceImageSubresourceLayout glad_debug_vkGetDeviceImageSubresourceLayout = glad_debug_impl_vkGetDeviceImageSubresourceLayout;
PFN_vkGetDeviceImageSubresourceLayoutKHR glad_vkGetDeviceImageSubresourceLayoutKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceImageSubresourceLayoutKHR(VkDevice device, const VkDeviceImageSubresourceInfo * pInfo, VkSubresourceLayout2 * pLayout) {
    _pre_call_vulkan_callback("vkGetDeviceImageSubresourceLayoutKHR", (GLADapiproc) glad_vkGetDeviceImageSubresourceLayoutKHR, 3, device, pInfo, pLayout);
    glad_vkGetDeviceImageSubresourceLayoutKHR(device, pInfo, pLayout);
    _post_call_vulkan_callback(NULL, "vkGetDeviceImageSubresourceLayoutKHR", (GLADapiproc) glad_vkGetDeviceImageSubresourceLayoutKHR, 3, device, pInfo, pLayout);
    
}
PFN_vkGetDeviceImageSubresourceLayoutKHR glad_debug_vkGetDeviceImageSubresourceLayoutKHR = glad_debug_impl_vkGetDeviceImageSubresourceLayoutKHR;
PFN_vkGetDeviceMemoryCommitment glad_vkGetDeviceMemoryCommitment = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize * pCommittedMemoryInBytes) {
    _pre_call_vulkan_callback("vkGetDeviceMemoryCommitment", (GLADapiproc) glad_vkGetDeviceMemoryCommitment, 3, device, memory, pCommittedMemoryInBytes);
    glad_vkGetDeviceMemoryCommitment(device, memory, pCommittedMemoryInBytes);
    _post_call_vulkan_callback(NULL, "vkGetDeviceMemoryCommitment", (GLADapiproc) glad_vkGetDeviceMemoryCommitment, 3, device, memory, pCommittedMemoryInBytes);
    
}
PFN_vkGetDeviceMemoryCommitment glad_debug_vkGetDeviceMemoryCommitment = glad_debug_impl_vkGetDeviceMemoryCommitment;
PFN_vkGetDeviceMemoryOpaqueCaptureAddress glad_vkGetDeviceMemoryOpaqueCaptureAddress = NULL;
static uint64_t GLAD_API_PTR glad_debug_impl_vkGetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo * pInfo) {
    uint64_t ret;
    _pre_call_vulkan_callback("vkGetDeviceMemoryOpaqueCaptureAddress", (GLADapiproc) glad_vkGetDeviceMemoryOpaqueCaptureAddress, 2, device, pInfo);
    ret = glad_vkGetDeviceMemoryOpaqueCaptureAddress(device, pInfo);
    _post_call_vulkan_callback((void*) &ret, "vkGetDeviceMemoryOpaqueCaptureAddress", (GLADapiproc) glad_vkGetDeviceMemoryOpaqueCaptureAddress, 2, device, pInfo);
    return ret;
}
PFN_vkGetDeviceMemoryOpaqueCaptureAddress glad_debug_vkGetDeviceMemoryOpaqueCaptureAddress = glad_debug_impl_vkGetDeviceMemoryOpaqueCaptureAddress;
PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR glad_vkGetDeviceMemoryOpaqueCaptureAddressKHR = NULL;
static uint64_t GLAD_API_PTR glad_debug_impl_vkGetDeviceMemoryOpaqueCaptureAddressKHR(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo * pInfo) {
    uint64_t ret;
    _pre_call_vulkan_callback("vkGetDeviceMemoryOpaqueCaptureAddressKHR", (GLADapiproc) glad_vkGetDeviceMemoryOpaqueCaptureAddressKHR, 2, device, pInfo);
    ret = glad_vkGetDeviceMemoryOpaqueCaptureAddressKHR(device, pInfo);
    _post_call_vulkan_callback((void*) &ret, "vkGetDeviceMemoryOpaqueCaptureAddressKHR", (GLADapiproc) glad_vkGetDeviceMemoryOpaqueCaptureAddressKHR, 2, device, pInfo);
    return ret;
}
PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR glad_debug_vkGetDeviceMemoryOpaqueCaptureAddressKHR = glad_debug_impl_vkGetDeviceMemoryOpaqueCaptureAddressKHR;
PFN_vkGetDeviceProcAddr glad_vkGetDeviceProcAddr = NULL;
static PFN_vkVoidFunction GLAD_API_PTR glad_debug_impl_vkGetDeviceProcAddr(VkDevice device, const char * pName) {
    PFN_vkVoidFunction ret;
    _pre_call_vulkan_callback("vkGetDeviceProcAddr", (GLADapiproc) glad_vkGetDeviceProcAddr, 2, device, pName);
    ret = glad_vkGetDeviceProcAddr(device, pName);
    _post_call_vulkan_callback((void*) &ret, "vkGetDeviceProcAddr", (GLADapiproc) glad_vkGetDeviceProcAddr, 2, device, pName);
    return ret;
}
PFN_vkGetDeviceProcAddr glad_debug_vkGetDeviceProcAddr = glad_debug_impl_vkGetDeviceProcAddr;
PFN_vkGetDeviceQueue glad_vkGetDeviceQueue = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue * pQueue) {
    _pre_call_vulkan_callback("vkGetDeviceQueue", (GLADapiproc) glad_vkGetDeviceQueue, 4, device, queueFamilyIndex, queueIndex, pQueue);
    glad_vkGetDeviceQueue(device, queueFamilyIndex, queueIndex, pQueue);
    _post_call_vulkan_callback(NULL, "vkGetDeviceQueue", (GLADapiproc) glad_vkGetDeviceQueue, 4, device, queueFamilyIndex, queueIndex, pQueue);
    
}
PFN_vkGetDeviceQueue glad_debug_vkGetDeviceQueue = glad_debug_impl_vkGetDeviceQueue;
PFN_vkGetDeviceQueue2 glad_vkGetDeviceQueue2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2 * pQueueInfo, VkQueue * pQueue) {
    _pre_call_vulkan_callback("vkGetDeviceQueue2", (GLADapiproc) glad_vkGetDeviceQueue2, 3, device, pQueueInfo, pQueue);
    glad_vkGetDeviceQueue2(device, pQueueInfo, pQueue);
    _post_call_vulkan_callback(NULL, "vkGetDeviceQueue2", (GLADapiproc) glad_vkGetDeviceQueue2, 3, device, pQueueInfo, pQueue);
    
}
PFN_vkGetDeviceQueue2 glad_debug_vkGetDeviceQueue2 = glad_debug_impl_vkGetDeviceQueue2;
PFN_vkGetEventStatus glad_vkGetEventStatus = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetEventStatus(VkDevice device, VkEvent event) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetEventStatus", (GLADapiproc) glad_vkGetEventStatus, 2, device, event);
    ret = glad_vkGetEventStatus(device, event);
    _post_call_vulkan_callback((void*) &ret, "vkGetEventStatus", (GLADapiproc) glad_vkGetEventStatus, 2, device, event);
    return ret;
}
PFN_vkGetEventStatus glad_debug_vkGetEventStatus = glad_debug_impl_vkGetEventStatus;
PFN_vkGetFenceStatus glad_vkGetFenceStatus = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetFenceStatus(VkDevice device, VkFence fence) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetFenceStatus", (GLADapiproc) glad_vkGetFenceStatus, 2, device, fence);
    ret = glad_vkGetFenceStatus(device, fence);
    _post_call_vulkan_callback((void*) &ret, "vkGetFenceStatus", (GLADapiproc) glad_vkGetFenceStatus, 2, device, fence);
    return ret;
}
PFN_vkGetFenceStatus glad_debug_vkGetFenceStatus = glad_debug_impl_vkGetFenceStatus;
PFN_vkGetImageMemoryRequirements glad_vkGetImageMemoryRequirements = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements * pMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetImageMemoryRequirements", (GLADapiproc) glad_vkGetImageMemoryRequirements, 3, device, image, pMemoryRequirements);
    glad_vkGetImageMemoryRequirements(device, image, pMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetImageMemoryRequirements", (GLADapiproc) glad_vkGetImageMemoryRequirements, 3, device, image, pMemoryRequirements);
    
}
PFN_vkGetImageMemoryRequirements glad_debug_vkGetImageMemoryRequirements = glad_debug_impl_vkGetImageMemoryRequirements;
PFN_vkGetImageMemoryRequirements2 glad_vkGetImageMemoryRequirements2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2 * pInfo, VkMemoryRequirements2 * pMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetImageMemoryRequirements2", (GLADapiproc) glad_vkGetImageMemoryRequirements2, 3, device, pInfo, pMemoryRequirements);
    glad_vkGetImageMemoryRequirements2(device, pInfo, pMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetImageMemoryRequirements2", (GLADapiproc) glad_vkGetImageMemoryRequirements2, 3, device, pInfo, pMemoryRequirements);
    
}
PFN_vkGetImageMemoryRequirements2 glad_debug_vkGetImageMemoryRequirements2 = glad_debug_impl_vkGetImageMemoryRequirements2;
PFN_vkGetImageMemoryRequirements2KHR glad_vkGetImageMemoryRequirements2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetImageMemoryRequirements2KHR(VkDevice device, const VkImageMemoryRequirementsInfo2 * pInfo, VkMemoryRequirements2 * pMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetImageMemoryRequirements2KHR", (GLADapiproc) glad_vkGetImageMemoryRequirements2KHR, 3, device, pInfo, pMemoryRequirements);
    glad_vkGetImageMemoryRequirements2KHR(device, pInfo, pMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetImageMemoryRequirements2KHR", (GLADapiproc) glad_vkGetImageMemoryRequirements2KHR, 3, device, pInfo, pMemoryRequirements);
    
}
PFN_vkGetImageMemoryRequirements2KHR glad_debug_vkGetImageMemoryRequirements2KHR = glad_debug_impl_vkGetImageMemoryRequirements2KHR;
PFN_vkGetImageSparseMemoryRequirements glad_vkGetImageSparseMemoryRequirements = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t * pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements * pSparseMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetImageSparseMemoryRequirements", (GLADapiproc) glad_vkGetImageSparseMemoryRequirements, 4, device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    glad_vkGetImageSparseMemoryRequirements(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetImageSparseMemoryRequirements", (GLADapiproc) glad_vkGetImageSparseMemoryRequirements, 4, device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    
}
PFN_vkGetImageSparseMemoryRequirements glad_debug_vkGetImageSparseMemoryRequirements = glad_debug_impl_vkGetImageSparseMemoryRequirements;
PFN_vkGetImageSparseMemoryRequirements2 glad_vkGetImageSparseMemoryRequirements2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetImageSparseMemoryRequirements2(VkDevice device, const VkImageSparseMemoryRequirementsInfo2 * pInfo, uint32_t * pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2 * pSparseMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetImageSparseMemoryRequirements2", (GLADapiproc) glad_vkGetImageSparseMemoryRequirements2, 4, device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    glad_vkGetImageSparseMemoryRequirements2(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetImageSparseMemoryRequirements2", (GLADapiproc) glad_vkGetImageSparseMemoryRequirements2, 4, device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    
}
PFN_vkGetImageSparseMemoryRequirements2 glad_debug_vkGetImageSparseMemoryRequirements2 = glad_debug_impl_vkGetImageSparseMemoryRequirements2;
PFN_vkGetImageSparseMemoryRequirements2KHR glad_vkGetImageSparseMemoryRequirements2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetImageSparseMemoryRequirements2KHR(VkDevice device, const VkImageSparseMemoryRequirementsInfo2 * pInfo, uint32_t * pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2 * pSparseMemoryRequirements) {
    _pre_call_vulkan_callback("vkGetImageSparseMemoryRequirements2KHR", (GLADapiproc) glad_vkGetImageSparseMemoryRequirements2KHR, 4, device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    glad_vkGetImageSparseMemoryRequirements2KHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    _post_call_vulkan_callback(NULL, "vkGetImageSparseMemoryRequirements2KHR", (GLADapiproc) glad_vkGetImageSparseMemoryRequirements2KHR, 4, device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
    
}
PFN_vkGetImageSparseMemoryRequirements2KHR glad_debug_vkGetImageSparseMemoryRequirements2KHR = glad_debug_impl_vkGetImageSparseMemoryRequirements2KHR;
PFN_vkGetImageSubresourceLayout glad_vkGetImageSubresourceLayout = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource * pSubresource, VkSubresourceLayout * pLayout) {
    _pre_call_vulkan_callback("vkGetImageSubresourceLayout", (GLADapiproc) glad_vkGetImageSubresourceLayout, 4, device, image, pSubresource, pLayout);
    glad_vkGetImageSubresourceLayout(device, image, pSubresource, pLayout);
    _post_call_vulkan_callback(NULL, "vkGetImageSubresourceLayout", (GLADapiproc) glad_vkGetImageSubresourceLayout, 4, device, image, pSubresource, pLayout);
    
}
PFN_vkGetImageSubresourceLayout glad_debug_vkGetImageSubresourceLayout = glad_debug_impl_vkGetImageSubresourceLayout;
PFN_vkGetImageSubresourceLayout2 glad_vkGetImageSubresourceLayout2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetImageSubresourceLayout2(VkDevice device, VkImage image, const VkImageSubresource2 * pSubresource, VkSubresourceLayout2 * pLayout) {
    _pre_call_vulkan_callback("vkGetImageSubresourceLayout2", (GLADapiproc) glad_vkGetImageSubresourceLayout2, 4, device, image, pSubresource, pLayout);
    glad_vkGetImageSubresourceLayout2(device, image, pSubresource, pLayout);
    _post_call_vulkan_callback(NULL, "vkGetImageSubresourceLayout2", (GLADapiproc) glad_vkGetImageSubresourceLayout2, 4, device, image, pSubresource, pLayout);
    
}
PFN_vkGetImageSubresourceLayout2 glad_debug_vkGetImageSubresourceLayout2 = glad_debug_impl_vkGetImageSubresourceLayout2;
PFN_vkGetImageSubresourceLayout2EXT glad_vkGetImageSubresourceLayout2EXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetImageSubresourceLayout2EXT(VkDevice device, VkImage image, const VkImageSubresource2 * pSubresource, VkSubresourceLayout2 * pLayout) {
    _pre_call_vulkan_callback("vkGetImageSubresourceLayout2EXT", (GLADapiproc) glad_vkGetImageSubresourceLayout2EXT, 4, device, image, pSubresource, pLayout);
    glad_vkGetImageSubresourceLayout2EXT(device, image, pSubresource, pLayout);
    _post_call_vulkan_callback(NULL, "vkGetImageSubresourceLayout2EXT", (GLADapiproc) glad_vkGetImageSubresourceLayout2EXT, 4, device, image, pSubresource, pLayout);
    
}
PFN_vkGetImageSubresourceLayout2EXT glad_debug_vkGetImageSubresourceLayout2EXT = glad_debug_impl_vkGetImageSubresourceLayout2EXT;
PFN_vkGetImageSubresourceLayout2KHR glad_vkGetImageSubresourceLayout2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetImageSubresourceLayout2KHR(VkDevice device, VkImage image, const VkImageSubresource2 * pSubresource, VkSubresourceLayout2 * pLayout) {
    _pre_call_vulkan_callback("vkGetImageSubresourceLayout2KHR", (GLADapiproc) glad_vkGetImageSubresourceLayout2KHR, 4, device, image, pSubresource, pLayout);
    glad_vkGetImageSubresourceLayout2KHR(device, image, pSubresource, pLayout);
    _post_call_vulkan_callback(NULL, "vkGetImageSubresourceLayout2KHR", (GLADapiproc) glad_vkGetImageSubresourceLayout2KHR, 4, device, image, pSubresource, pLayout);
    
}
PFN_vkGetImageSubresourceLayout2KHR glad_debug_vkGetImageSubresourceLayout2KHR = glad_debug_impl_vkGetImageSubresourceLayout2KHR;
PFN_vkGetInstanceProcAddr glad_vkGetInstanceProcAddr = NULL;
static PFN_vkVoidFunction GLAD_API_PTR glad_debug_impl_vkGetInstanceProcAddr(VkInstance instance, const char * pName) {
    PFN_vkVoidFunction ret;
    _pre_call_vulkan_callback("vkGetInstanceProcAddr", (GLADapiproc) glad_vkGetInstanceProcAddr, 2, instance, pName);
    ret = glad_vkGetInstanceProcAddr(instance, pName);
    _post_call_vulkan_callback((void*) &ret, "vkGetInstanceProcAddr", (GLADapiproc) glad_vkGetInstanceProcAddr, 2, instance, pName);
    return ret;
}
PFN_vkGetInstanceProcAddr glad_debug_vkGetInstanceProcAddr = glad_debug_impl_vkGetInstanceProcAddr;
PFN_vkGetPhysicalDeviceExternalBufferProperties glad_vkGetPhysicalDeviceExternalBufferProperties = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceExternalBufferProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfo * pExternalBufferInfo, VkExternalBufferProperties * pExternalBufferProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceExternalBufferProperties", (GLADapiproc) glad_vkGetPhysicalDeviceExternalBufferProperties, 3, physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
    glad_vkGetPhysicalDeviceExternalBufferProperties(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceExternalBufferProperties", (GLADapiproc) glad_vkGetPhysicalDeviceExternalBufferProperties, 3, physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
    
}
PFN_vkGetPhysicalDeviceExternalBufferProperties glad_debug_vkGetPhysicalDeviceExternalBufferProperties = glad_debug_impl_vkGetPhysicalDeviceExternalBufferProperties;
PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR glad_vkGetPhysicalDeviceExternalBufferPropertiesKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceExternalBufferPropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfo * pExternalBufferInfo, VkExternalBufferProperties * pExternalBufferProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceExternalBufferPropertiesKHR", (GLADapiproc) glad_vkGetPhysicalDeviceExternalBufferPropertiesKHR, 3, physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
    glad_vkGetPhysicalDeviceExternalBufferPropertiesKHR(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceExternalBufferPropertiesKHR", (GLADapiproc) glad_vkGetPhysicalDeviceExternalBufferPropertiesKHR, 3, physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
    
}
PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR glad_debug_vkGetPhysicalDeviceExternalBufferPropertiesKHR = glad_debug_impl_vkGetPhysicalDeviceExternalBufferPropertiesKHR;
PFN_vkGetPhysicalDeviceExternalFenceProperties glad_vkGetPhysicalDeviceExternalFenceProperties = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceExternalFenceProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo * pExternalFenceInfo, VkExternalFenceProperties * pExternalFenceProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceExternalFenceProperties", (GLADapiproc) glad_vkGetPhysicalDeviceExternalFenceProperties, 3, physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
    glad_vkGetPhysicalDeviceExternalFenceProperties(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceExternalFenceProperties", (GLADapiproc) glad_vkGetPhysicalDeviceExternalFenceProperties, 3, physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
    
}
PFN_vkGetPhysicalDeviceExternalFenceProperties glad_debug_vkGetPhysicalDeviceExternalFenceProperties = glad_debug_impl_vkGetPhysicalDeviceExternalFenceProperties;
PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR glad_vkGetPhysicalDeviceExternalFencePropertiesKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceExternalFencePropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo * pExternalFenceInfo, VkExternalFenceProperties * pExternalFenceProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceExternalFencePropertiesKHR", (GLADapiproc) glad_vkGetPhysicalDeviceExternalFencePropertiesKHR, 3, physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
    glad_vkGetPhysicalDeviceExternalFencePropertiesKHR(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceExternalFencePropertiesKHR", (GLADapiproc) glad_vkGetPhysicalDeviceExternalFencePropertiesKHR, 3, physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
    
}
PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR glad_debug_vkGetPhysicalDeviceExternalFencePropertiesKHR = glad_debug_impl_vkGetPhysicalDeviceExternalFencePropertiesKHR;
PFN_vkGetPhysicalDeviceExternalSemaphoreProperties glad_vkGetPhysicalDeviceExternalSemaphoreProperties = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceExternalSemaphoreProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfo * pExternalSemaphoreInfo, VkExternalSemaphoreProperties * pExternalSemaphoreProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceExternalSemaphoreProperties", (GLADapiproc) glad_vkGetPhysicalDeviceExternalSemaphoreProperties, 3, physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
    glad_vkGetPhysicalDeviceExternalSemaphoreProperties(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceExternalSemaphoreProperties", (GLADapiproc) glad_vkGetPhysicalDeviceExternalSemaphoreProperties, 3, physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
    
}
PFN_vkGetPhysicalDeviceExternalSemaphoreProperties glad_debug_vkGetPhysicalDeviceExternalSemaphoreProperties = glad_debug_impl_vkGetPhysicalDeviceExternalSemaphoreProperties;
PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR glad_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfo * pExternalSemaphoreInfo, VkExternalSemaphoreProperties * pExternalSemaphoreProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceExternalSemaphorePropertiesKHR", (GLADapiproc) glad_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR, 3, physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
    glad_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR", (GLADapiproc) glad_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR, 3, physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
    
}
PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR glad_debug_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = glad_debug_impl_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR;
PFN_vkGetPhysicalDeviceFeatures glad_vkGetPhysicalDeviceFeatures = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures * pFeatures) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceFeatures", (GLADapiproc) glad_vkGetPhysicalDeviceFeatures, 2, physicalDevice, pFeatures);
    glad_vkGetPhysicalDeviceFeatures(physicalDevice, pFeatures);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceFeatures", (GLADapiproc) glad_vkGetPhysicalDeviceFeatures, 2, physicalDevice, pFeatures);
    
}
PFN_vkGetPhysicalDeviceFeatures glad_debug_vkGetPhysicalDeviceFeatures = glad_debug_impl_vkGetPhysicalDeviceFeatures;
PFN_vkGetPhysicalDeviceFeatures2 glad_vkGetPhysicalDeviceFeatures2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2 * pFeatures) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceFeatures2", (GLADapiproc) glad_vkGetPhysicalDeviceFeatures2, 2, physicalDevice, pFeatures);
    glad_vkGetPhysicalDeviceFeatures2(physicalDevice, pFeatures);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceFeatures2", (GLADapiproc) glad_vkGetPhysicalDeviceFeatures2, 2, physicalDevice, pFeatures);
    
}
PFN_vkGetPhysicalDeviceFeatures2 glad_debug_vkGetPhysicalDeviceFeatures2 = glad_debug_impl_vkGetPhysicalDeviceFeatures2;
PFN_vkGetPhysicalDeviceFeatures2KHR glad_vkGetPhysicalDeviceFeatures2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceFeatures2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2 * pFeatures) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceFeatures2KHR", (GLADapiproc) glad_vkGetPhysicalDeviceFeatures2KHR, 2, physicalDevice, pFeatures);
    glad_vkGetPhysicalDeviceFeatures2KHR(physicalDevice, pFeatures);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceFeatures2KHR", (GLADapiproc) glad_vkGetPhysicalDeviceFeatures2KHR, 2, physicalDevice, pFeatures);
    
}
PFN_vkGetPhysicalDeviceFeatures2KHR glad_debug_vkGetPhysicalDeviceFeatures2KHR = glad_debug_impl_vkGetPhysicalDeviceFeatures2KHR;
PFN_vkGetPhysicalDeviceFormatProperties glad_vkGetPhysicalDeviceFormatProperties = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties * pFormatProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceFormatProperties", (GLADapiproc) glad_vkGetPhysicalDeviceFormatProperties, 3, physicalDevice, format, pFormatProperties);
    glad_vkGetPhysicalDeviceFormatProperties(physicalDevice, format, pFormatProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceFormatProperties", (GLADapiproc) glad_vkGetPhysicalDeviceFormatProperties, 3, physicalDevice, format, pFormatProperties);
    
}
PFN_vkGetPhysicalDeviceFormatProperties glad_debug_vkGetPhysicalDeviceFormatProperties = glad_debug_impl_vkGetPhysicalDeviceFormatProperties;
PFN_vkGetPhysicalDeviceFormatProperties2 glad_vkGetPhysicalDeviceFormatProperties2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceFormatProperties2(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2 * pFormatProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceFormatProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceFormatProperties2, 3, physicalDevice, format, pFormatProperties);
    glad_vkGetPhysicalDeviceFormatProperties2(physicalDevice, format, pFormatProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceFormatProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceFormatProperties2, 3, physicalDevice, format, pFormatProperties);
    
}
PFN_vkGetPhysicalDeviceFormatProperties2 glad_debug_vkGetPhysicalDeviceFormatProperties2 = glad_debug_impl_vkGetPhysicalDeviceFormatProperties2;
PFN_vkGetPhysicalDeviceFormatProperties2KHR glad_vkGetPhysicalDeviceFormatProperties2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceFormatProperties2KHR(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2 * pFormatProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceFormatProperties2KHR", (GLADapiproc) glad_vkGetPhysicalDeviceFormatProperties2KHR, 3, physicalDevice, format, pFormatProperties);
    glad_vkGetPhysicalDeviceFormatProperties2KHR(physicalDevice, format, pFormatProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceFormatProperties2KHR", (GLADapiproc) glad_vkGetPhysicalDeviceFormatProperties2KHR, 3, physicalDevice, format, pFormatProperties);
    
}
PFN_vkGetPhysicalDeviceFormatProperties2KHR glad_debug_vkGetPhysicalDeviceFormatProperties2KHR = glad_debug_impl_vkGetPhysicalDeviceFormatProperties2KHR;
PFN_vkGetPhysicalDeviceImageFormatProperties glad_vkGetPhysicalDeviceImageFormatProperties = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties * pImageFormatProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPhysicalDeviceImageFormatProperties", (GLADapiproc) glad_vkGetPhysicalDeviceImageFormatProperties, 7, physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties);
    ret = glad_vkGetPhysicalDeviceImageFormatProperties(physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties);
    _post_call_vulkan_callback((void*) &ret, "vkGetPhysicalDeviceImageFormatProperties", (GLADapiproc) glad_vkGetPhysicalDeviceImageFormatProperties, 7, physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties);
    return ret;
}
PFN_vkGetPhysicalDeviceImageFormatProperties glad_debug_vkGetPhysicalDeviceImageFormatProperties = glad_debug_impl_vkGetPhysicalDeviceImageFormatProperties;
PFN_vkGetPhysicalDeviceImageFormatProperties2 glad_vkGetPhysicalDeviceImageFormatProperties2 = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2 * pImageFormatInfo, VkImageFormatProperties2 * pImageFormatProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPhysicalDeviceImageFormatProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceImageFormatProperties2, 3, physicalDevice, pImageFormatInfo, pImageFormatProperties);
    ret = glad_vkGetPhysicalDeviceImageFormatProperties2(physicalDevice, pImageFormatInfo, pImageFormatProperties);
    _post_call_vulkan_callback((void*) &ret, "vkGetPhysicalDeviceImageFormatProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceImageFormatProperties2, 3, physicalDevice, pImageFormatInfo, pImageFormatProperties);
    return ret;
}
PFN_vkGetPhysicalDeviceImageFormatProperties2 glad_debug_vkGetPhysicalDeviceImageFormatProperties2 = glad_debug_impl_vkGetPhysicalDeviceImageFormatProperties2;
PFN_vkGetPhysicalDeviceImageFormatProperties2KHR glad_vkGetPhysicalDeviceImageFormatProperties2KHR = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2 * pImageFormatInfo, VkImageFormatProperties2 * pImageFormatProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPhysicalDeviceImageFormatProperties2KHR", (GLADapiproc) glad_vkGetPhysicalDeviceImageFormatProperties2KHR, 3, physicalDevice, pImageFormatInfo, pImageFormatProperties);
    ret = glad_vkGetPhysicalDeviceImageFormatProperties2KHR(physicalDevice, pImageFormatInfo, pImageFormatProperties);
    _post_call_vulkan_callback((void*) &ret, "vkGetPhysicalDeviceImageFormatProperties2KHR", (GLADapiproc) glad_vkGetPhysicalDeviceImageFormatProperties2KHR, 3, physicalDevice, pImageFormatInfo, pImageFormatProperties);
    return ret;
}
PFN_vkGetPhysicalDeviceImageFormatProperties2KHR glad_debug_vkGetPhysicalDeviceImageFormatProperties2KHR = glad_debug_impl_vkGetPhysicalDeviceImageFormatProperties2KHR;
PFN_vkGetPhysicalDeviceMemoryProperties glad_vkGetPhysicalDeviceMemoryProperties = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties * pMemoryProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceMemoryProperties", (GLADapiproc) glad_vkGetPhysicalDeviceMemoryProperties, 2, physicalDevice, pMemoryProperties);
    glad_vkGetPhysicalDeviceMemoryProperties(physicalDevice, pMemoryProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceMemoryProperties", (GLADapiproc) glad_vkGetPhysicalDeviceMemoryProperties, 2, physicalDevice, pMemoryProperties);
    
}
PFN_vkGetPhysicalDeviceMemoryProperties glad_debug_vkGetPhysicalDeviceMemoryProperties = glad_debug_impl_vkGetPhysicalDeviceMemoryProperties;
PFN_vkGetPhysicalDeviceMemoryProperties2 glad_vkGetPhysicalDeviceMemoryProperties2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceMemoryProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2 * pMemoryProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceMemoryProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceMemoryProperties2, 2, physicalDevice, pMemoryProperties);
    glad_vkGetPhysicalDeviceMemoryProperties2(physicalDevice, pMemoryProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceMemoryProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceMemoryProperties2, 2, physicalDevice, pMemoryProperties);
    
}
PFN_vkGetPhysicalDeviceMemoryProperties2 glad_debug_vkGetPhysicalDeviceMemoryProperties2 = glad_debug_impl_vkGetPhysicalDeviceMemoryProperties2;
PFN_vkGetPhysicalDeviceMemoryProperties2KHR glad_vkGetPhysicalDeviceMemoryProperties2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceMemoryProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2 * pMemoryProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceMemoryProperties2KHR", (GLADapiproc) glad_vkGetPhysicalDeviceMemoryProperties2KHR, 2, physicalDevice, pMemoryProperties);
    glad_vkGetPhysicalDeviceMemoryProperties2KHR(physicalDevice, pMemoryProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceMemoryProperties2KHR", (GLADapiproc) glad_vkGetPhysicalDeviceMemoryProperties2KHR, 2, physicalDevice, pMemoryProperties);
    
}
PFN_vkGetPhysicalDeviceMemoryProperties2KHR glad_debug_vkGetPhysicalDeviceMemoryProperties2KHR = glad_debug_impl_vkGetPhysicalDeviceMemoryProperties2KHR;
PFN_vkGetPhysicalDevicePresentRectanglesKHR glad_vkGetPhysicalDevicePresentRectanglesKHR = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPhysicalDevicePresentRectanglesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t * pRectCount, VkRect2D * pRects) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPhysicalDevicePresentRectanglesKHR", (GLADapiproc) glad_vkGetPhysicalDevicePresentRectanglesKHR, 4, physicalDevice, surface, pRectCount, pRects);
    ret = glad_vkGetPhysicalDevicePresentRectanglesKHR(physicalDevice, surface, pRectCount, pRects);
    _post_call_vulkan_callback((void*) &ret, "vkGetPhysicalDevicePresentRectanglesKHR", (GLADapiproc) glad_vkGetPhysicalDevicePresentRectanglesKHR, 4, physicalDevice, surface, pRectCount, pRects);
    return ret;
}
PFN_vkGetPhysicalDevicePresentRectanglesKHR glad_debug_vkGetPhysicalDevicePresentRectanglesKHR = glad_debug_impl_vkGetPhysicalDevicePresentRectanglesKHR;
PFN_vkGetPhysicalDeviceProperties glad_vkGetPhysicalDeviceProperties = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties * pProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceProperties", (GLADapiproc) glad_vkGetPhysicalDeviceProperties, 2, physicalDevice, pProperties);
    glad_vkGetPhysicalDeviceProperties(physicalDevice, pProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceProperties", (GLADapiproc) glad_vkGetPhysicalDeviceProperties, 2, physicalDevice, pProperties);
    
}
PFN_vkGetPhysicalDeviceProperties glad_debug_vkGetPhysicalDeviceProperties = glad_debug_impl_vkGetPhysicalDeviceProperties;
PFN_vkGetPhysicalDeviceProperties2 glad_vkGetPhysicalDeviceProperties2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2 * pProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceProperties2, 2, physicalDevice, pProperties);
    glad_vkGetPhysicalDeviceProperties2(physicalDevice, pProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceProperties2, 2, physicalDevice, pProperties);
    
}
PFN_vkGetPhysicalDeviceProperties2 glad_debug_vkGetPhysicalDeviceProperties2 = glad_debug_impl_vkGetPhysicalDeviceProperties2;
PFN_vkGetPhysicalDeviceProperties2KHR glad_vkGetPhysicalDeviceProperties2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2 * pProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceProperties2KHR", (GLADapiproc) glad_vkGetPhysicalDeviceProperties2KHR, 2, physicalDevice, pProperties);
    glad_vkGetPhysicalDeviceProperties2KHR(physicalDevice, pProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceProperties2KHR", (GLADapiproc) glad_vkGetPhysicalDeviceProperties2KHR, 2, physicalDevice, pProperties);
    
}
PFN_vkGetPhysicalDeviceProperties2KHR glad_debug_vkGetPhysicalDeviceProperties2KHR = glad_debug_impl_vkGetPhysicalDeviceProperties2KHR;
PFN_vkGetPhysicalDeviceQueueFamilyProperties glad_vkGetPhysicalDeviceQueueFamilyProperties = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t * pQueueFamilyPropertyCount, VkQueueFamilyProperties * pQueueFamilyProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceQueueFamilyProperties", (GLADapiproc) glad_vkGetPhysicalDeviceQueueFamilyProperties, 3, physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    glad_vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceQueueFamilyProperties", (GLADapiproc) glad_vkGetPhysicalDeviceQueueFamilyProperties, 3, physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    
}
PFN_vkGetPhysicalDeviceQueueFamilyProperties glad_debug_vkGetPhysicalDeviceQueueFamilyProperties = glad_debug_impl_vkGetPhysicalDeviceQueueFamilyProperties;
PFN_vkGetPhysicalDeviceQueueFamilyProperties2 glad_vkGetPhysicalDeviceQueueFamilyProperties2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceQueueFamilyProperties2(VkPhysicalDevice physicalDevice, uint32_t * pQueueFamilyPropertyCount, VkQueueFamilyProperties2 * pQueueFamilyProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceQueueFamilyProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceQueueFamilyProperties2, 3, physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    glad_vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceQueueFamilyProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceQueueFamilyProperties2, 3, physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    
}
PFN_vkGetPhysicalDeviceQueueFamilyProperties2 glad_debug_vkGetPhysicalDeviceQueueFamilyProperties2 = glad_debug_impl_vkGetPhysicalDeviceQueueFamilyProperties2;
PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR glad_vkGetPhysicalDeviceQueueFamilyProperties2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceQueueFamilyProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t * pQueueFamilyPropertyCount, VkQueueFamilyProperties2 * pQueueFamilyProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceQueueFamilyProperties2KHR", (GLADapiproc) glad_vkGetPhysicalDeviceQueueFamilyProperties2KHR, 3, physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    glad_vkGetPhysicalDeviceQueueFamilyProperties2KHR(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceQueueFamilyProperties2KHR", (GLADapiproc) glad_vkGetPhysicalDeviceQueueFamilyProperties2KHR, 3, physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
    
}
PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR glad_debug_vkGetPhysicalDeviceQueueFamilyProperties2KHR = glad_debug_impl_vkGetPhysicalDeviceQueueFamilyProperties2KHR;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties glad_vkGetPhysicalDeviceSparseImageFormatProperties = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, uint32_t * pPropertyCount, VkSparseImageFormatProperties * pProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceSparseImageFormatProperties", (GLADapiproc) glad_vkGetPhysicalDeviceSparseImageFormatProperties, 8, physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties);
    glad_vkGetPhysicalDeviceSparseImageFormatProperties(physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceSparseImageFormatProperties", (GLADapiproc) glad_vkGetPhysicalDeviceSparseImageFormatProperties, 8, physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties);
    
}
PFN_vkGetPhysicalDeviceSparseImageFormatProperties glad_debug_vkGetPhysicalDeviceSparseImageFormatProperties = glad_debug_impl_vkGetPhysicalDeviceSparseImageFormatProperties;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 glad_vkGetPhysicalDeviceSparseImageFormatProperties2 = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceSparseImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2 * pFormatInfo, uint32_t * pPropertyCount, VkSparseImageFormatProperties2 * pProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceSparseImageFormatProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceSparseImageFormatProperties2, 4, physicalDevice, pFormatInfo, pPropertyCount, pProperties);
    glad_vkGetPhysicalDeviceSparseImageFormatProperties2(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceSparseImageFormatProperties2", (GLADapiproc) glad_vkGetPhysicalDeviceSparseImageFormatProperties2, 4, physicalDevice, pFormatInfo, pPropertyCount, pProperties);
    
}
PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 glad_debug_vkGetPhysicalDeviceSparseImageFormatProperties2 = glad_debug_impl_vkGetPhysicalDeviceSparseImageFormatProperties2;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR glad_vkGetPhysicalDeviceSparseImageFormatProperties2KHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceSparseImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2 * pFormatInfo, uint32_t * pPropertyCount, VkSparseImageFormatProperties2 * pProperties) {
    _pre_call_vulkan_callback("vkGetPhysicalDeviceSparseImageFormatProperties2KHR", (GLADapiproc) glad_vkGetPhysicalDeviceSparseImageFormatProperties2KHR, 4, physicalDevice, pFormatInfo, pPropertyCount, pProperties);
    glad_vkGetPhysicalDeviceSparseImageFormatProperties2KHR(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
    _post_call_vulkan_callback(NULL, "vkGetPhysicalDeviceSparseImageFormatProperties2KHR", (GLADapiproc) glad_vkGetPhysicalDeviceSparseImageFormatProperties2KHR, 4, physicalDevice, pFormatInfo, pPropertyCount, pProperties);
    
}
PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR glad_debug_vkGetPhysicalDeviceSparseImageFormatProperties2KHR = glad_debug_impl_vkGetPhysicalDeviceSparseImageFormatProperties2KHR;
PFN_vkGetPhysicalDeviceToolProperties glad_vkGetPhysicalDeviceToolProperties = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceToolProperties(VkPhysicalDevice physicalDevice, uint32_t * pToolCount, VkPhysicalDeviceToolProperties * pToolProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPhysicalDeviceToolProperties", (GLADapiproc) glad_vkGetPhysicalDeviceToolProperties, 3, physicalDevice, pToolCount, pToolProperties);
    ret = glad_vkGetPhysicalDeviceToolProperties(physicalDevice, pToolCount, pToolProperties);
    _post_call_vulkan_callback((void*) &ret, "vkGetPhysicalDeviceToolProperties", (GLADapiproc) glad_vkGetPhysicalDeviceToolProperties, 3, physicalDevice, pToolCount, pToolProperties);
    return ret;
}
PFN_vkGetPhysicalDeviceToolProperties glad_debug_vkGetPhysicalDeviceToolProperties = glad_debug_impl_vkGetPhysicalDeviceToolProperties;
PFN_vkGetPhysicalDeviceToolPropertiesEXT glad_vkGetPhysicalDeviceToolPropertiesEXT = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPhysicalDeviceToolPropertiesEXT(VkPhysicalDevice physicalDevice, uint32_t * pToolCount, VkPhysicalDeviceToolProperties * pToolProperties) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPhysicalDeviceToolPropertiesEXT", (GLADapiproc) glad_vkGetPhysicalDeviceToolPropertiesEXT, 3, physicalDevice, pToolCount, pToolProperties);
    ret = glad_vkGetPhysicalDeviceToolPropertiesEXT(physicalDevice, pToolCount, pToolProperties);
    _post_call_vulkan_callback((void*) &ret, "vkGetPhysicalDeviceToolPropertiesEXT", (GLADapiproc) glad_vkGetPhysicalDeviceToolPropertiesEXT, 3, physicalDevice, pToolCount, pToolProperties);
    return ret;
}
PFN_vkGetPhysicalDeviceToolPropertiesEXT glad_debug_vkGetPhysicalDeviceToolPropertiesEXT = glad_debug_impl_vkGetPhysicalDeviceToolPropertiesEXT;
PFN_vkGetPipelineCacheData glad_vkGetPipelineCacheData = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t * pDataSize, void * pData) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetPipelineCacheData", (GLADapiproc) glad_vkGetPipelineCacheData, 4, device, pipelineCache, pDataSize, pData);
    ret = glad_vkGetPipelineCacheData(device, pipelineCache, pDataSize, pData);
    _post_call_vulkan_callback((void*) &ret, "vkGetPipelineCacheData", (GLADapiproc) glad_vkGetPipelineCacheData, 4, device, pipelineCache, pDataSize, pData);
    return ret;
}
PFN_vkGetPipelineCacheData glad_debug_vkGetPipelineCacheData = glad_debug_impl_vkGetPipelineCacheData;
PFN_vkGetPrivateData glad_vkGetPrivateData = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t * pData) {
    _pre_call_vulkan_callback("vkGetPrivateData", (GLADapiproc) glad_vkGetPrivateData, 5, device, objectType, objectHandle, privateDataSlot, pData);
    glad_vkGetPrivateData(device, objectType, objectHandle, privateDataSlot, pData);
    _post_call_vulkan_callback(NULL, "vkGetPrivateData", (GLADapiproc) glad_vkGetPrivateData, 5, device, objectType, objectHandle, privateDataSlot, pData);
    
}
PFN_vkGetPrivateData glad_debug_vkGetPrivateData = glad_debug_impl_vkGetPrivateData;
PFN_vkGetPrivateDataEXT glad_vkGetPrivateDataEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t * pData) {
    _pre_call_vulkan_callback("vkGetPrivateDataEXT", (GLADapiproc) glad_vkGetPrivateDataEXT, 5, device, objectType, objectHandle, privateDataSlot, pData);
    glad_vkGetPrivateDataEXT(device, objectType, objectHandle, privateDataSlot, pData);
    _post_call_vulkan_callback(NULL, "vkGetPrivateDataEXT", (GLADapiproc) glad_vkGetPrivateDataEXT, 5, device, objectType, objectHandle, privateDataSlot, pData);
    
}
PFN_vkGetPrivateDataEXT glad_debug_vkGetPrivateDataEXT = glad_debug_impl_vkGetPrivateDataEXT;
PFN_vkGetQueryPoolResults glad_vkGetQueryPoolResults = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void * pData, VkDeviceSize stride, VkQueryResultFlags flags) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetQueryPoolResults", (GLADapiproc) glad_vkGetQueryPoolResults, 8, device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
    ret = glad_vkGetQueryPoolResults(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
    _post_call_vulkan_callback((void*) &ret, "vkGetQueryPoolResults", (GLADapiproc) glad_vkGetQueryPoolResults, 8, device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
    return ret;
}
PFN_vkGetQueryPoolResults glad_debug_vkGetQueryPoolResults = glad_debug_impl_vkGetQueryPoolResults;
PFN_vkGetRenderAreaGranularity glad_vkGetRenderAreaGranularity = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D * pGranularity) {
    _pre_call_vulkan_callback("vkGetRenderAreaGranularity", (GLADapiproc) glad_vkGetRenderAreaGranularity, 3, device, renderPass, pGranularity);
    glad_vkGetRenderAreaGranularity(device, renderPass, pGranularity);
    _post_call_vulkan_callback(NULL, "vkGetRenderAreaGranularity", (GLADapiproc) glad_vkGetRenderAreaGranularity, 3, device, renderPass, pGranularity);
    
}
PFN_vkGetRenderAreaGranularity glad_debug_vkGetRenderAreaGranularity = glad_debug_impl_vkGetRenderAreaGranularity;
PFN_vkGetRenderingAreaGranularity glad_vkGetRenderingAreaGranularity = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetRenderingAreaGranularity(VkDevice device, const VkRenderingAreaInfo * pRenderingAreaInfo, VkExtent2D * pGranularity) {
    _pre_call_vulkan_callback("vkGetRenderingAreaGranularity", (GLADapiproc) glad_vkGetRenderingAreaGranularity, 3, device, pRenderingAreaInfo, pGranularity);
    glad_vkGetRenderingAreaGranularity(device, pRenderingAreaInfo, pGranularity);
    _post_call_vulkan_callback(NULL, "vkGetRenderingAreaGranularity", (GLADapiproc) glad_vkGetRenderingAreaGranularity, 3, device, pRenderingAreaInfo, pGranularity);
    
}
PFN_vkGetRenderingAreaGranularity glad_debug_vkGetRenderingAreaGranularity = glad_debug_impl_vkGetRenderingAreaGranularity;
PFN_vkGetRenderingAreaGranularityKHR glad_vkGetRenderingAreaGranularityKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkGetRenderingAreaGranularityKHR(VkDevice device, const VkRenderingAreaInfo * pRenderingAreaInfo, VkExtent2D * pGranularity) {
    _pre_call_vulkan_callback("vkGetRenderingAreaGranularityKHR", (GLADapiproc) glad_vkGetRenderingAreaGranularityKHR, 3, device, pRenderingAreaInfo, pGranularity);
    glad_vkGetRenderingAreaGranularityKHR(device, pRenderingAreaInfo, pGranularity);
    _post_call_vulkan_callback(NULL, "vkGetRenderingAreaGranularityKHR", (GLADapiproc) glad_vkGetRenderingAreaGranularityKHR, 3, device, pRenderingAreaInfo, pGranularity);
    
}
PFN_vkGetRenderingAreaGranularityKHR glad_debug_vkGetRenderingAreaGranularityKHR = glad_debug_impl_vkGetRenderingAreaGranularityKHR;
PFN_vkGetSemaphoreCounterValue glad_vkGetSemaphoreCounterValue = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t * pValue) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetSemaphoreCounterValue", (GLADapiproc) glad_vkGetSemaphoreCounterValue, 3, device, semaphore, pValue);
    ret = glad_vkGetSemaphoreCounterValue(device, semaphore, pValue);
    _post_call_vulkan_callback((void*) &ret, "vkGetSemaphoreCounterValue", (GLADapiproc) glad_vkGetSemaphoreCounterValue, 3, device, semaphore, pValue);
    return ret;
}
PFN_vkGetSemaphoreCounterValue glad_debug_vkGetSemaphoreCounterValue = glad_debug_impl_vkGetSemaphoreCounterValue;
PFN_vkGetSemaphoreCounterValueKHR glad_vkGetSemaphoreCounterValueKHR = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetSemaphoreCounterValueKHR(VkDevice device, VkSemaphore semaphore, uint64_t * pValue) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetSemaphoreCounterValueKHR", (GLADapiproc) glad_vkGetSemaphoreCounterValueKHR, 3, device, semaphore, pValue);
    ret = glad_vkGetSemaphoreCounterValueKHR(device, semaphore, pValue);
    _post_call_vulkan_callback((void*) &ret, "vkGetSemaphoreCounterValueKHR", (GLADapiproc) glad_vkGetSemaphoreCounterValueKHR, 3, device, semaphore, pValue);
    return ret;
}
PFN_vkGetSemaphoreCounterValueKHR glad_debug_vkGetSemaphoreCounterValueKHR = glad_debug_impl_vkGetSemaphoreCounterValueKHR;
PFN_vkGetShaderBinaryDataEXT glad_vkGetShaderBinaryDataEXT = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkGetShaderBinaryDataEXT(VkDevice device, VkShaderEXT shader, size_t * pDataSize, void * pData) {
    VkResult ret;
    _pre_call_vulkan_callback("vkGetShaderBinaryDataEXT", (GLADapiproc) glad_vkGetShaderBinaryDataEXT, 4, device, shader, pDataSize, pData);
    ret = glad_vkGetShaderBinaryDataEXT(device, shader, pDataSize, pData);
    _post_call_vulkan_callback((void*) &ret, "vkGetShaderBinaryDataEXT", (GLADapiproc) glad_vkGetShaderBinaryDataEXT, 4, device, shader, pDataSize, pData);
    return ret;
}
PFN_vkGetShaderBinaryDataEXT glad_debug_vkGetShaderBinaryDataEXT = glad_debug_impl_vkGetShaderBinaryDataEXT;
PFN_vkInvalidateMappedMemoryRanges glad_vkInvalidateMappedMemoryRanges = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange * pMemoryRanges) {
    VkResult ret;
    _pre_call_vulkan_callback("vkInvalidateMappedMemoryRanges", (GLADapiproc) glad_vkInvalidateMappedMemoryRanges, 3, device, memoryRangeCount, pMemoryRanges);
    ret = glad_vkInvalidateMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
    _post_call_vulkan_callback((void*) &ret, "vkInvalidateMappedMemoryRanges", (GLADapiproc) glad_vkInvalidateMappedMemoryRanges, 3, device, memoryRangeCount, pMemoryRanges);
    return ret;
}
PFN_vkInvalidateMappedMemoryRanges glad_debug_vkInvalidateMappedMemoryRanges = glad_debug_impl_vkInvalidateMappedMemoryRanges;
PFN_vkMapMemory glad_vkMapMemory = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkMapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void ** ppData) {
    VkResult ret;
    _pre_call_vulkan_callback("vkMapMemory", (GLADapiproc) glad_vkMapMemory, 6, device, memory, offset, size, flags, ppData);
    ret = glad_vkMapMemory(device, memory, offset, size, flags, ppData);
    _post_call_vulkan_callback((void*) &ret, "vkMapMemory", (GLADapiproc) glad_vkMapMemory, 6, device, memory, offset, size, flags, ppData);
    return ret;
}
PFN_vkMapMemory glad_debug_vkMapMemory = glad_debug_impl_vkMapMemory;
PFN_vkMapMemory2 glad_vkMapMemory2 = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkMapMemory2(VkDevice device, const VkMemoryMapInfo * pMemoryMapInfo, void ** ppData) {
    VkResult ret;
    _pre_call_vulkan_callback("vkMapMemory2", (GLADapiproc) glad_vkMapMemory2, 3, device, pMemoryMapInfo, ppData);
    ret = glad_vkMapMemory2(device, pMemoryMapInfo, ppData);
    _post_call_vulkan_callback((void*) &ret, "vkMapMemory2", (GLADapiproc) glad_vkMapMemory2, 3, device, pMemoryMapInfo, ppData);
    return ret;
}
PFN_vkMapMemory2 glad_debug_vkMapMemory2 = glad_debug_impl_vkMapMemory2;
PFN_vkMapMemory2KHR glad_vkMapMemory2KHR = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkMapMemory2KHR(VkDevice device, const VkMemoryMapInfo * pMemoryMapInfo, void ** ppData) {
    VkResult ret;
    _pre_call_vulkan_callback("vkMapMemory2KHR", (GLADapiproc) glad_vkMapMemory2KHR, 3, device, pMemoryMapInfo, ppData);
    ret = glad_vkMapMemory2KHR(device, pMemoryMapInfo, ppData);
    _post_call_vulkan_callback((void*) &ret, "vkMapMemory2KHR", (GLADapiproc) glad_vkMapMemory2KHR, 3, device, pMemoryMapInfo, ppData);
    return ret;
}
PFN_vkMapMemory2KHR glad_debug_vkMapMemory2KHR = glad_debug_impl_vkMapMemory2KHR;
PFN_vkMergePipelineCaches glad_vkMergePipelineCaches = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkMergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache * pSrcCaches) {
    VkResult ret;
    _pre_call_vulkan_callback("vkMergePipelineCaches", (GLADapiproc) glad_vkMergePipelineCaches, 4, device, dstCache, srcCacheCount, pSrcCaches);
    ret = glad_vkMergePipelineCaches(device, dstCache, srcCacheCount, pSrcCaches);
    _post_call_vulkan_callback((void*) &ret, "vkMergePipelineCaches", (GLADapiproc) glad_vkMergePipelineCaches, 4, device, dstCache, srcCacheCount, pSrcCaches);
    return ret;
}
PFN_vkMergePipelineCaches glad_debug_vkMergePipelineCaches = glad_debug_impl_vkMergePipelineCaches;
PFN_vkQueueBindSparse glad_vkQueueBindSparse = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo * pBindInfo, VkFence fence) {
    VkResult ret;
    _pre_call_vulkan_callback("vkQueueBindSparse", (GLADapiproc) glad_vkQueueBindSparse, 4, queue, bindInfoCount, pBindInfo, fence);
    ret = glad_vkQueueBindSparse(queue, bindInfoCount, pBindInfo, fence);
    _post_call_vulkan_callback((void*) &ret, "vkQueueBindSparse", (GLADapiproc) glad_vkQueueBindSparse, 4, queue, bindInfoCount, pBindInfo, fence);
    return ret;
}
PFN_vkQueueBindSparse glad_debug_vkQueueBindSparse = glad_debug_impl_vkQueueBindSparse;
PFN_vkQueueSubmit glad_vkQueueSubmit = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkQueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo * pSubmits, VkFence fence) {
    VkResult ret;
    _pre_call_vulkan_callback("vkQueueSubmit", (GLADapiproc) glad_vkQueueSubmit, 4, queue, submitCount, pSubmits, fence);
    ret = glad_vkQueueSubmit(queue, submitCount, pSubmits, fence);
    _post_call_vulkan_callback((void*) &ret, "vkQueueSubmit", (GLADapiproc) glad_vkQueueSubmit, 4, queue, submitCount, pSubmits, fence);
    return ret;
}
PFN_vkQueueSubmit glad_debug_vkQueueSubmit = glad_debug_impl_vkQueueSubmit;
PFN_vkQueueSubmit2 glad_vkQueueSubmit2 = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkQueueSubmit2(VkQueue queue, uint32_t submitCount, const VkSubmitInfo2 * pSubmits, VkFence fence) {
    VkResult ret;
    _pre_call_vulkan_callback("vkQueueSubmit2", (GLADapiproc) glad_vkQueueSubmit2, 4, queue, submitCount, pSubmits, fence);
    ret = glad_vkQueueSubmit2(queue, submitCount, pSubmits, fence);
    _post_call_vulkan_callback((void*) &ret, "vkQueueSubmit2", (GLADapiproc) glad_vkQueueSubmit2, 4, queue, submitCount, pSubmits, fence);
    return ret;
}
PFN_vkQueueSubmit2 glad_debug_vkQueueSubmit2 = glad_debug_impl_vkQueueSubmit2;
PFN_vkQueueSubmit2KHR glad_vkQueueSubmit2KHR = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkQueueSubmit2KHR(VkQueue queue, uint32_t submitCount, const VkSubmitInfo2 * pSubmits, VkFence fence) {
    VkResult ret;
    _pre_call_vulkan_callback("vkQueueSubmit2KHR", (GLADapiproc) glad_vkQueueSubmit2KHR, 4, queue, submitCount, pSubmits, fence);
    ret = glad_vkQueueSubmit2KHR(queue, submitCount, pSubmits, fence);
    _post_call_vulkan_callback((void*) &ret, "vkQueueSubmit2KHR", (GLADapiproc) glad_vkQueueSubmit2KHR, 4, queue, submitCount, pSubmits, fence);
    return ret;
}
PFN_vkQueueSubmit2KHR glad_debug_vkQueueSubmit2KHR = glad_debug_impl_vkQueueSubmit2KHR;
PFN_vkQueueWaitIdle glad_vkQueueWaitIdle = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkQueueWaitIdle(VkQueue queue) {
    VkResult ret;
    _pre_call_vulkan_callback("vkQueueWaitIdle", (GLADapiproc) glad_vkQueueWaitIdle, 1, queue);
    ret = glad_vkQueueWaitIdle(queue);
    _post_call_vulkan_callback((void*) &ret, "vkQueueWaitIdle", (GLADapiproc) glad_vkQueueWaitIdle, 1, queue);
    return ret;
}
PFN_vkQueueWaitIdle glad_debug_vkQueueWaitIdle = glad_debug_impl_vkQueueWaitIdle;
PFN_vkResetCommandBuffer glad_vkResetCommandBuffer = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) {
    VkResult ret;
    _pre_call_vulkan_callback("vkResetCommandBuffer", (GLADapiproc) glad_vkResetCommandBuffer, 2, commandBuffer, flags);
    ret = glad_vkResetCommandBuffer(commandBuffer, flags);
    _post_call_vulkan_callback((void*) &ret, "vkResetCommandBuffer", (GLADapiproc) glad_vkResetCommandBuffer, 2, commandBuffer, flags);
    return ret;
}
PFN_vkResetCommandBuffer glad_debug_vkResetCommandBuffer = glad_debug_impl_vkResetCommandBuffer;
PFN_vkResetCommandPool glad_vkResetCommandPool = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) {
    VkResult ret;
    _pre_call_vulkan_callback("vkResetCommandPool", (GLADapiproc) glad_vkResetCommandPool, 3, device, commandPool, flags);
    ret = glad_vkResetCommandPool(device, commandPool, flags);
    _post_call_vulkan_callback((void*) &ret, "vkResetCommandPool", (GLADapiproc) glad_vkResetCommandPool, 3, device, commandPool, flags);
    return ret;
}
PFN_vkResetCommandPool glad_debug_vkResetCommandPool = glad_debug_impl_vkResetCommandPool;
PFN_vkResetDescriptorPool glad_vkResetDescriptorPool = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags) {
    VkResult ret;
    _pre_call_vulkan_callback("vkResetDescriptorPool", (GLADapiproc) glad_vkResetDescriptorPool, 3, device, descriptorPool, flags);
    ret = glad_vkResetDescriptorPool(device, descriptorPool, flags);
    _post_call_vulkan_callback((void*) &ret, "vkResetDescriptorPool", (GLADapiproc) glad_vkResetDescriptorPool, 3, device, descriptorPool, flags);
    return ret;
}
PFN_vkResetDescriptorPool glad_debug_vkResetDescriptorPool = glad_debug_impl_vkResetDescriptorPool;
PFN_vkResetEvent glad_vkResetEvent = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkResetEvent(VkDevice device, VkEvent event) {
    VkResult ret;
    _pre_call_vulkan_callback("vkResetEvent", (GLADapiproc) glad_vkResetEvent, 2, device, event);
    ret = glad_vkResetEvent(device, event);
    _post_call_vulkan_callback((void*) &ret, "vkResetEvent", (GLADapiproc) glad_vkResetEvent, 2, device, event);
    return ret;
}
PFN_vkResetEvent glad_debug_vkResetEvent = glad_debug_impl_vkResetEvent;
PFN_vkResetFences glad_vkResetFences = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkResetFences(VkDevice device, uint32_t fenceCount, const VkFence * pFences) {
    VkResult ret;
    _pre_call_vulkan_callback("vkResetFences", (GLADapiproc) glad_vkResetFences, 3, device, fenceCount, pFences);
    ret = glad_vkResetFences(device, fenceCount, pFences);
    _post_call_vulkan_callback((void*) &ret, "vkResetFences", (GLADapiproc) glad_vkResetFences, 3, device, fenceCount, pFences);
    return ret;
}
PFN_vkResetFences glad_debug_vkResetFences = glad_debug_impl_vkResetFences;
PFN_vkResetQueryPool glad_vkResetQueryPool = NULL;
static void GLAD_API_PTR glad_debug_impl_vkResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) {
    _pre_call_vulkan_callback("vkResetQueryPool", (GLADapiproc) glad_vkResetQueryPool, 4, device, queryPool, firstQuery, queryCount);
    glad_vkResetQueryPool(device, queryPool, firstQuery, queryCount);
    _post_call_vulkan_callback(NULL, "vkResetQueryPool", (GLADapiproc) glad_vkResetQueryPool, 4, device, queryPool, firstQuery, queryCount);
    
}
PFN_vkResetQueryPool glad_debug_vkResetQueryPool = glad_debug_impl_vkResetQueryPool;
PFN_vkResetQueryPoolEXT glad_vkResetQueryPoolEXT = NULL;
static void GLAD_API_PTR glad_debug_impl_vkResetQueryPoolEXT(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) {
    _pre_call_vulkan_callback("vkResetQueryPoolEXT", (GLADapiproc) glad_vkResetQueryPoolEXT, 4, device, queryPool, firstQuery, queryCount);
    glad_vkResetQueryPoolEXT(device, queryPool, firstQuery, queryCount);
    _post_call_vulkan_callback(NULL, "vkResetQueryPoolEXT", (GLADapiproc) glad_vkResetQueryPoolEXT, 4, device, queryPool, firstQuery, queryCount);
    
}
PFN_vkResetQueryPoolEXT glad_debug_vkResetQueryPoolEXT = glad_debug_impl_vkResetQueryPoolEXT;
PFN_vkSetEvent glad_vkSetEvent = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkSetEvent(VkDevice device, VkEvent event) {
    VkResult ret;
    _pre_call_vulkan_callback("vkSetEvent", (GLADapiproc) glad_vkSetEvent, 2, device, event);
    ret = glad_vkSetEvent(device, event);
    _post_call_vulkan_callback((void*) &ret, "vkSetEvent", (GLADapiproc) glad_vkSetEvent, 2, device, event);
    return ret;
}
PFN_vkSetEvent glad_debug_vkSetEvent = glad_debug_impl_vkSetEvent;
PFN_vkSetPrivateData glad_vkSetPrivateData = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkSetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) {
    VkResult ret;
    _pre_call_vulkan_callback("vkSetPrivateData", (GLADapiproc) glad_vkSetPrivateData, 5, device, objectType, objectHandle, privateDataSlot, data);
    ret = glad_vkSetPrivateData(device, objectType, objectHandle, privateDataSlot, data);
    _post_call_vulkan_callback((void*) &ret, "vkSetPrivateData", (GLADapiproc) glad_vkSetPrivateData, 5, device, objectType, objectHandle, privateDataSlot, data);
    return ret;
}
PFN_vkSetPrivateData glad_debug_vkSetPrivateData = glad_debug_impl_vkSetPrivateData;
PFN_vkSetPrivateDataEXT glad_vkSetPrivateDataEXT = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkSetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) {
    VkResult ret;
    _pre_call_vulkan_callback("vkSetPrivateDataEXT", (GLADapiproc) glad_vkSetPrivateDataEXT, 5, device, objectType, objectHandle, privateDataSlot, data);
    ret = glad_vkSetPrivateDataEXT(device, objectType, objectHandle, privateDataSlot, data);
    _post_call_vulkan_callback((void*) &ret, "vkSetPrivateDataEXT", (GLADapiproc) glad_vkSetPrivateDataEXT, 5, device, objectType, objectHandle, privateDataSlot, data);
    return ret;
}
PFN_vkSetPrivateDataEXT glad_debug_vkSetPrivateDataEXT = glad_debug_impl_vkSetPrivateDataEXT;
PFN_vkSignalSemaphore glad_vkSignalSemaphore = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkSignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo * pSignalInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkSignalSemaphore", (GLADapiproc) glad_vkSignalSemaphore, 2, device, pSignalInfo);
    ret = glad_vkSignalSemaphore(device, pSignalInfo);
    _post_call_vulkan_callback((void*) &ret, "vkSignalSemaphore", (GLADapiproc) glad_vkSignalSemaphore, 2, device, pSignalInfo);
    return ret;
}
PFN_vkSignalSemaphore glad_debug_vkSignalSemaphore = glad_debug_impl_vkSignalSemaphore;
PFN_vkSignalSemaphoreKHR glad_vkSignalSemaphoreKHR = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkSignalSemaphoreKHR(VkDevice device, const VkSemaphoreSignalInfo * pSignalInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkSignalSemaphoreKHR", (GLADapiproc) glad_vkSignalSemaphoreKHR, 2, device, pSignalInfo);
    ret = glad_vkSignalSemaphoreKHR(device, pSignalInfo);
    _post_call_vulkan_callback((void*) &ret, "vkSignalSemaphoreKHR", (GLADapiproc) glad_vkSignalSemaphoreKHR, 2, device, pSignalInfo);
    return ret;
}
PFN_vkSignalSemaphoreKHR glad_debug_vkSignalSemaphoreKHR = glad_debug_impl_vkSignalSemaphoreKHR;
PFN_vkTransitionImageLayout glad_vkTransitionImageLayout = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkTransitionImageLayout(VkDevice device, uint32_t transitionCount, const VkHostImageLayoutTransitionInfo * pTransitions) {
    VkResult ret;
    _pre_call_vulkan_callback("vkTransitionImageLayout", (GLADapiproc) glad_vkTransitionImageLayout, 3, device, transitionCount, pTransitions);
    ret = glad_vkTransitionImageLayout(device, transitionCount, pTransitions);
    _post_call_vulkan_callback((void*) &ret, "vkTransitionImageLayout", (GLADapiproc) glad_vkTransitionImageLayout, 3, device, transitionCount, pTransitions);
    return ret;
}
PFN_vkTransitionImageLayout glad_debug_vkTransitionImageLayout = glad_debug_impl_vkTransitionImageLayout;
PFN_vkTransitionImageLayoutEXT glad_vkTransitionImageLayoutEXT = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkTransitionImageLayoutEXT(VkDevice device, uint32_t transitionCount, const VkHostImageLayoutTransitionInfo * pTransitions) {
    VkResult ret;
    _pre_call_vulkan_callback("vkTransitionImageLayoutEXT", (GLADapiproc) glad_vkTransitionImageLayoutEXT, 3, device, transitionCount, pTransitions);
    ret = glad_vkTransitionImageLayoutEXT(device, transitionCount, pTransitions);
    _post_call_vulkan_callback((void*) &ret, "vkTransitionImageLayoutEXT", (GLADapiproc) glad_vkTransitionImageLayoutEXT, 3, device, transitionCount, pTransitions);
    return ret;
}
PFN_vkTransitionImageLayoutEXT glad_debug_vkTransitionImageLayoutEXT = glad_debug_impl_vkTransitionImageLayoutEXT;
PFN_vkTrimCommandPool glad_vkTrimCommandPool = NULL;
static void GLAD_API_PTR glad_debug_impl_vkTrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) {
    _pre_call_vulkan_callback("vkTrimCommandPool", (GLADapiproc) glad_vkTrimCommandPool, 3, device, commandPool, flags);
    glad_vkTrimCommandPool(device, commandPool, flags);
    _post_call_vulkan_callback(NULL, "vkTrimCommandPool", (GLADapiproc) glad_vkTrimCommandPool, 3, device, commandPool, flags);
    
}
PFN_vkTrimCommandPool glad_debug_vkTrimCommandPool = glad_debug_impl_vkTrimCommandPool;
PFN_vkTrimCommandPoolKHR glad_vkTrimCommandPoolKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkTrimCommandPoolKHR(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) {
    _pre_call_vulkan_callback("vkTrimCommandPoolKHR", (GLADapiproc) glad_vkTrimCommandPoolKHR, 3, device, commandPool, flags);
    glad_vkTrimCommandPoolKHR(device, commandPool, flags);
    _post_call_vulkan_callback(NULL, "vkTrimCommandPoolKHR", (GLADapiproc) glad_vkTrimCommandPoolKHR, 3, device, commandPool, flags);
    
}
PFN_vkTrimCommandPoolKHR glad_debug_vkTrimCommandPoolKHR = glad_debug_impl_vkTrimCommandPoolKHR;
PFN_vkUnmapMemory glad_vkUnmapMemory = NULL;
static void GLAD_API_PTR glad_debug_impl_vkUnmapMemory(VkDevice device, VkDeviceMemory memory) {
    _pre_call_vulkan_callback("vkUnmapMemory", (GLADapiproc) glad_vkUnmapMemory, 2, device, memory);
    glad_vkUnmapMemory(device, memory);
    _post_call_vulkan_callback(NULL, "vkUnmapMemory", (GLADapiproc) glad_vkUnmapMemory, 2, device, memory);
    
}
PFN_vkUnmapMemory glad_debug_vkUnmapMemory = glad_debug_impl_vkUnmapMemory;
PFN_vkUnmapMemory2 glad_vkUnmapMemory2 = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkUnmapMemory2(VkDevice device, const VkMemoryUnmapInfo * pMemoryUnmapInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkUnmapMemory2", (GLADapiproc) glad_vkUnmapMemory2, 2, device, pMemoryUnmapInfo);
    ret = glad_vkUnmapMemory2(device, pMemoryUnmapInfo);
    _post_call_vulkan_callback((void*) &ret, "vkUnmapMemory2", (GLADapiproc) glad_vkUnmapMemory2, 2, device, pMemoryUnmapInfo);
    return ret;
}
PFN_vkUnmapMemory2 glad_debug_vkUnmapMemory2 = glad_debug_impl_vkUnmapMemory2;
PFN_vkUnmapMemory2KHR glad_vkUnmapMemory2KHR = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkUnmapMemory2KHR(VkDevice device, const VkMemoryUnmapInfo * pMemoryUnmapInfo) {
    VkResult ret;
    _pre_call_vulkan_callback("vkUnmapMemory2KHR", (GLADapiproc) glad_vkUnmapMemory2KHR, 2, device, pMemoryUnmapInfo);
    ret = glad_vkUnmapMemory2KHR(device, pMemoryUnmapInfo);
    _post_call_vulkan_callback((void*) &ret, "vkUnmapMemory2KHR", (GLADapiproc) glad_vkUnmapMemory2KHR, 2, device, pMemoryUnmapInfo);
    return ret;
}
PFN_vkUnmapMemory2KHR glad_debug_vkUnmapMemory2KHR = glad_debug_impl_vkUnmapMemory2KHR;
PFN_vkUpdateDescriptorSetWithTemplate glad_vkUpdateDescriptorSetWithTemplate = NULL;
static void GLAD_API_PTR glad_debug_impl_vkUpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void * pData) {
    _pre_call_vulkan_callback("vkUpdateDescriptorSetWithTemplate", (GLADapiproc) glad_vkUpdateDescriptorSetWithTemplate, 4, device, descriptorSet, descriptorUpdateTemplate, pData);
    glad_vkUpdateDescriptorSetWithTemplate(device, descriptorSet, descriptorUpdateTemplate, pData);
    _post_call_vulkan_callback(NULL, "vkUpdateDescriptorSetWithTemplate", (GLADapiproc) glad_vkUpdateDescriptorSetWithTemplate, 4, device, descriptorSet, descriptorUpdateTemplate, pData);
    
}
PFN_vkUpdateDescriptorSetWithTemplate glad_debug_vkUpdateDescriptorSetWithTemplate = glad_debug_impl_vkUpdateDescriptorSetWithTemplate;
PFN_vkUpdateDescriptorSetWithTemplateKHR glad_vkUpdateDescriptorSetWithTemplateKHR = NULL;
static void GLAD_API_PTR glad_debug_impl_vkUpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void * pData) {
    _pre_call_vulkan_callback("vkUpdateDescriptorSetWithTemplateKHR", (GLADapiproc) glad_vkUpdateDescriptorSetWithTemplateKHR, 4, device, descriptorSet, descriptorUpdateTemplate, pData);
    glad_vkUpdateDescriptorSetWithTemplateKHR(device, descriptorSet, descriptorUpdateTemplate, pData);
    _post_call_vulkan_callback(NULL, "vkUpdateDescriptorSetWithTemplateKHR", (GLADapiproc) glad_vkUpdateDescriptorSetWithTemplateKHR, 4, device, descriptorSet, descriptorUpdateTemplate, pData);
    
}
PFN_vkUpdateDescriptorSetWithTemplateKHR glad_debug_vkUpdateDescriptorSetWithTemplateKHR = glad_debug_impl_vkUpdateDescriptorSetWithTemplateKHR;
PFN_vkUpdateDescriptorSets glad_vkUpdateDescriptorSets = NULL;
static void GLAD_API_PTR glad_debug_impl_vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet * pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet * pDescriptorCopies) {
    _pre_call_vulkan_callback("vkUpdateDescriptorSets", (GLADapiproc) glad_vkUpdateDescriptorSets, 5, device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
    glad_vkUpdateDescriptorSets(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
    _post_call_vulkan_callback(NULL, "vkUpdateDescriptorSets", (GLADapiproc) glad_vkUpdateDescriptorSets, 5, device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
    
}
PFN_vkUpdateDescriptorSets glad_debug_vkUpdateDescriptorSets = glad_debug_impl_vkUpdateDescriptorSets;
PFN_vkWaitForFences glad_vkWaitForFences = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkWaitForFences(VkDevice device, uint32_t fenceCount, const VkFence * pFences, VkBool32 waitAll, uint64_t timeout) {
    VkResult ret;
    _pre_call_vulkan_callback("vkWaitForFences", (GLADapiproc) glad_vkWaitForFences, 5, device, fenceCount, pFences, waitAll, timeout);
    ret = glad_vkWaitForFences(device, fenceCount, pFences, waitAll, timeout);
    _post_call_vulkan_callback((void*) &ret, "vkWaitForFences", (GLADapiproc) glad_vkWaitForFences, 5, device, fenceCount, pFences, waitAll, timeout);
    return ret;
}
PFN_vkWaitForFences glad_debug_vkWaitForFences = glad_debug_impl_vkWaitForFences;
PFN_vkWaitSemaphores glad_vkWaitSemaphores = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkWaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo * pWaitInfo, uint64_t timeout) {
    VkResult ret;
    _pre_call_vulkan_callback("vkWaitSemaphores", (GLADapiproc) glad_vkWaitSemaphores, 3, device, pWaitInfo, timeout);
    ret = glad_vkWaitSemaphores(device, pWaitInfo, timeout);
    _post_call_vulkan_callback((void*) &ret, "vkWaitSemaphores", (GLADapiproc) glad_vkWaitSemaphores, 3, device, pWaitInfo, timeout);
    return ret;
}
PFN_vkWaitSemaphores glad_debug_vkWaitSemaphores = glad_debug_impl_vkWaitSemaphores;
PFN_vkWaitSemaphoresKHR glad_vkWaitSemaphoresKHR = NULL;
static VkResult GLAD_API_PTR glad_debug_impl_vkWaitSemaphoresKHR(VkDevice device, const VkSemaphoreWaitInfo * pWaitInfo, uint64_t timeout) {
    VkResult ret;
    _pre_call_vulkan_callback("vkWaitSemaphoresKHR", (GLADapiproc) glad_vkWaitSemaphoresKHR, 3, device, pWaitInfo, timeout);
    ret = glad_vkWaitSemaphoresKHR(device, pWaitInfo, timeout);
    _post_call_vulkan_callback((void*) &ret, "vkWaitSemaphoresKHR", (GLADapiproc) glad_vkWaitSemaphoresKHR, 3, device, pWaitInfo, timeout);
    return ret;
}
PFN_vkWaitSemaphoresKHR glad_debug_vkWaitSemaphoresKHR = glad_debug_impl_vkWaitSemaphoresKHR;


static void glad_vk_load_VK_VERSION_1_0( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_VERSION_1_0) return;
    glad_vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers) load(userptr, "vkAllocateCommandBuffers");
    glad_vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets) load(userptr, "vkAllocateDescriptorSets");
    glad_vkAllocateMemory = (PFN_vkAllocateMemory) load(userptr, "vkAllocateMemory");
    glad_vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer) load(userptr, "vkBeginCommandBuffer");
    glad_vkBindBufferMemory = (PFN_vkBindBufferMemory) load(userptr, "vkBindBufferMemory");
    glad_vkBindImageMemory = (PFN_vkBindImageMemory) load(userptr, "vkBindImageMemory");
    glad_vkCmdBeginQuery = (PFN_vkCmdBeginQuery) load(userptr, "vkCmdBeginQuery");
    glad_vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass) load(userptr, "vkCmdBeginRenderPass");
    glad_vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets) load(userptr, "vkCmdBindDescriptorSets");
    glad_vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer) load(userptr, "vkCmdBindIndexBuffer");
    glad_vkCmdBindPipeline = (PFN_vkCmdBindPipeline) load(userptr, "vkCmdBindPipeline");
    glad_vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers) load(userptr, "vkCmdBindVertexBuffers");
    glad_vkCmdBlitImage = (PFN_vkCmdBlitImage) load(userptr, "vkCmdBlitImage");
    glad_vkCmdClearAttachments = (PFN_vkCmdClearAttachments) load(userptr, "vkCmdClearAttachments");
    glad_vkCmdClearColorImage = (PFN_vkCmdClearColorImage) load(userptr, "vkCmdClearColorImage");
    glad_vkCmdClearDepthStencilImage = (PFN_vkCmdClearDepthStencilImage) load(userptr, "vkCmdClearDepthStencilImage");
    glad_vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer) load(userptr, "vkCmdCopyBuffer");
    glad_vkCmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage) load(userptr, "vkCmdCopyBufferToImage");
    glad_vkCmdCopyImage = (PFN_vkCmdCopyImage) load(userptr, "vkCmdCopyImage");
    glad_vkCmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer) load(userptr, "vkCmdCopyImageToBuffer");
    glad_vkCmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults) load(userptr, "vkCmdCopyQueryPoolResults");
    glad_vkCmdDispatch = (PFN_vkCmdDispatch) load(userptr, "vkCmdDispatch");
    glad_vkCmdDispatchIndirect = (PFN_vkCmdDispatchIndirect) load(userptr, "vkCmdDispatchIndirect");
    glad_vkCmdDraw = (PFN_vkCmdDraw) load(userptr, "vkCmdDraw");
    glad_vkCmdDrawIndexed = (PFN_vkCmdDrawIndexed) load(userptr, "vkCmdDrawIndexed");
    glad_vkCmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect) load(userptr, "vkCmdDrawIndexedIndirect");
    glad_vkCmdDrawIndirect = (PFN_vkCmdDrawIndirect) load(userptr, "vkCmdDrawIndirect");
    glad_vkCmdEndQuery = (PFN_vkCmdEndQuery) load(userptr, "vkCmdEndQuery");
    glad_vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass) load(userptr, "vkCmdEndRenderPass");
    glad_vkCmdExecuteCommands = (PFN_vkCmdExecuteCommands) load(userptr, "vkCmdExecuteCommands");
    glad_vkCmdFillBuffer = (PFN_vkCmdFillBuffer) load(userptr, "vkCmdFillBuffer");
    glad_vkCmdNextSubpass = (PFN_vkCmdNextSubpass) load(userptr, "vkCmdNextSubpass");
    glad_vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier) load(userptr, "vkCmdPipelineBarrier");
    glad_vkCmdPushConstants = (PFN_vkCmdPushConstants) load(userptr, "vkCmdPushConstants");
    glad_vkCmdResetEvent = (PFN_vkCmdResetEvent) load(userptr, "vkCmdResetEvent");
    glad_vkCmdResetQueryPool = (PFN_vkCmdResetQueryPool) load(userptr, "vkCmdResetQueryPool");
    glad_vkCmdResolveImage = (PFN_vkCmdResolveImage) load(userptr, "vkCmdResolveImage");
    glad_vkCmdSetBlendConstants = (PFN_vkCmdSetBlendConstants) load(userptr, "vkCmdSetBlendConstants");
    glad_vkCmdSetDepthBias = (PFN_vkCmdSetDepthBias) load(userptr, "vkCmdSetDepthBias");
    glad_vkCmdSetDepthBounds = (PFN_vkCmdSetDepthBounds) load(userptr, "vkCmdSetDepthBounds");
    glad_vkCmdSetEvent = (PFN_vkCmdSetEvent) load(userptr, "vkCmdSetEvent");
    glad_vkCmdSetLineWidth = (PFN_vkCmdSetLineWidth) load(userptr, "vkCmdSetLineWidth");
    glad_vkCmdSetScissor = (PFN_vkCmdSetScissor) load(userptr, "vkCmdSetScissor");
    glad_vkCmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask) load(userptr, "vkCmdSetStencilCompareMask");
    glad_vkCmdSetStencilReference = (PFN_vkCmdSetStencilReference) load(userptr, "vkCmdSetStencilReference");
    glad_vkCmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask) load(userptr, "vkCmdSetStencilWriteMask");
    glad_vkCmdSetViewport = (PFN_vkCmdSetViewport) load(userptr, "vkCmdSetViewport");
    glad_vkCmdUpdateBuffer = (PFN_vkCmdUpdateBuffer) load(userptr, "vkCmdUpdateBuffer");
    glad_vkCmdWaitEvents = (PFN_vkCmdWaitEvents) load(userptr, "vkCmdWaitEvents");
    glad_vkCmdWriteTimestamp = (PFN_vkCmdWriteTimestamp) load(userptr, "vkCmdWriteTimestamp");
    glad_vkCreateBuffer = (PFN_vkCreateBuffer) load(userptr, "vkCreateBuffer");
    glad_vkCreateBufferView = (PFN_vkCreateBufferView) load(userptr, "vkCreateBufferView");
    glad_vkCreateCommandPool = (PFN_vkCreateCommandPool) load(userptr, "vkCreateCommandPool");
    glad_vkCreateComputePipelines = (PFN_vkCreateComputePipelines) load(userptr, "vkCreateComputePipelines");
    glad_vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool) load(userptr, "vkCreateDescriptorPool");
    glad_vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout) load(userptr, "vkCreateDescriptorSetLayout");
    glad_vkCreateDevice = (PFN_vkCreateDevice) load(userptr, "vkCreateDevice");
    glad_vkCreateEvent = (PFN_vkCreateEvent) load(userptr, "vkCreateEvent");
    glad_vkCreateFence = (PFN_vkCreateFence) load(userptr, "vkCreateFence");
    glad_vkCreateFramebuffer = (PFN_vkCreateFramebuffer) load(userptr, "vkCreateFramebuffer");
    glad_vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines) load(userptr, "vkCreateGraphicsPipelines");
    glad_vkCreateImage = (PFN_vkCreateImage) load(userptr, "vkCreateImage");
    glad_vkCreateImageView = (PFN_vkCreateImageView) load(userptr, "vkCreateImageView");
    glad_vkCreateInstance = (PFN_vkCreateInstance) load(userptr, "vkCreateInstance");
    glad_vkCreatePipelineCache = (PFN_vkCreatePipelineCache) load(userptr, "vkCreatePipelineCache");
    glad_vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout) load(userptr, "vkCreatePipelineLayout");
    glad_vkCreateQueryPool = (PFN_vkCreateQueryPool) load(userptr, "vkCreateQueryPool");
    glad_vkCreateRenderPass = (PFN_vkCreateRenderPass) load(userptr, "vkCreateRenderPass");
    glad_vkCreateSampler = (PFN_vkCreateSampler) load(userptr, "vkCreateSampler");
    glad_vkCreateSemaphore = (PFN_vkCreateSemaphore) load(userptr, "vkCreateSemaphore");
    glad_vkCreateShaderModule = (PFN_vkCreateShaderModule) load(userptr, "vkCreateShaderModule");
    glad_vkDestroyBuffer = (PFN_vkDestroyBuffer) load(userptr, "vkDestroyBuffer");
    glad_vkDestroyBufferView = (PFN_vkDestroyBufferView) load(userptr, "vkDestroyBufferView");
    glad_vkDestroyCommandPool = (PFN_vkDestroyCommandPool) load(userptr, "vkDestroyCommandPool");
    glad_vkDestroyDescriptorPool = (PFN_vkDestroyDescriptorPool) load(userptr, "vkDestroyDescriptorPool");
    glad_vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout) load(userptr, "vkDestroyDescriptorSetLayout");
    glad_vkDestroyDevice = (PFN_vkDestroyDevice) load(userptr, "vkDestroyDevice");
    glad_vkDestroyEvent = (PFN_vkDestroyEvent) load(userptr, "vkDestroyEvent");
    glad_vkDestroyFence = (PFN_vkDestroyFence) load(userptr, "vkDestroyFence");
    glad_vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer) load(userptr, "vkDestroyFramebuffer");
    glad_vkDestroyImage = (PFN_vkDestroyImage) load(userptr, "vkDestroyImage");
    glad_vkDestroyImageView = (PFN_vkDestroyImageView) load(userptr, "vkDestroyImageView");
    glad_vkDestroyInstance = (PFN_vkDestroyInstance) load(userptr, "vkDestroyInstance");
    glad_vkDestroyPipeline = (PFN_vkDestroyPipeline) load(userptr, "vkDestroyPipeline");
    glad_vkDestroyPipelineCache = (PFN_vkDestroyPipelineCache) load(userptr, "vkDestroyPipelineCache");
    glad_vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout) load(userptr, "vkDestroyPipelineLayout");
    glad_vkDestroyQueryPool = (PFN_vkDestroyQueryPool) load(userptr, "vkDestroyQueryPool");
    glad_vkDestroyRenderPass = (PFN_vkDestroyRenderPass) load(userptr, "vkDestroyRenderPass");
    glad_vkDestroySampler = (PFN_vkDestroySampler) load(userptr, "vkDestroySampler");
    glad_vkDestroySemaphore = (PFN_vkDestroySemaphore) load(userptr, "vkDestroySemaphore");
    glad_vkDestroyShaderModule = (PFN_vkDestroyShaderModule) load(userptr, "vkDestroyShaderModule");
    glad_vkDeviceWaitIdle = (PFN_vkDeviceWaitIdle) load(userptr, "vkDeviceWaitIdle");
    glad_vkEndCommandBuffer = (PFN_vkEndCommandBuffer) load(userptr, "vkEndCommandBuffer");
    glad_vkEnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties) load(userptr, "vkEnumerateDeviceExtensionProperties");
    glad_vkEnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties) load(userptr, "vkEnumerateDeviceLayerProperties");
    glad_vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties) load(userptr, "vkEnumerateInstanceExtensionProperties");
    glad_vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties) load(userptr, "vkEnumerateInstanceLayerProperties");
    glad_vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices) load(userptr, "vkEnumeratePhysicalDevices");
    glad_vkFlushMappedMemoryRanges = (PFN_vkFlushMappedMemoryRanges) load(userptr, "vkFlushMappedMemoryRanges");
    glad_vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers) load(userptr, "vkFreeCommandBuffers");
    glad_vkFreeDescriptorSets = (PFN_vkFreeDescriptorSets) load(userptr, "vkFreeDescriptorSets");
    glad_vkFreeMemory = (PFN_vkFreeMemory) load(userptr, "vkFreeMemory");
    glad_vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements) load(userptr, "vkGetBufferMemoryRequirements");
    glad_vkGetDeviceMemoryCommitment = (PFN_vkGetDeviceMemoryCommitment) load(userptr, "vkGetDeviceMemoryCommitment");
    glad_vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr) load(userptr, "vkGetDeviceProcAddr");
    glad_vkGetDeviceQueue = (PFN_vkGetDeviceQueue) load(userptr, "vkGetDeviceQueue");
    glad_vkGetEventStatus = (PFN_vkGetEventStatus) load(userptr, "vkGetEventStatus");
    glad_vkGetFenceStatus = (PFN_vkGetFenceStatus) load(userptr, "vkGetFenceStatus");
    glad_vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements) load(userptr, "vkGetImageMemoryRequirements");
    glad_vkGetImageSparseMemoryRequirements = (PFN_vkGetImageSparseMemoryRequirements) load(userptr, "vkGetImageSparseMemoryRequirements");
    glad_vkGetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout) load(userptr, "vkGetImageSubresourceLayout");
    glad_vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr) load(userptr, "vkGetInstanceProcAddr");
    glad_vkGetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures) load(userptr, "vkGetPhysicalDeviceFeatures");
    glad_vkGetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties) load(userptr, "vkGetPhysicalDeviceFormatProperties");
    glad_vkGetPhysicalDeviceImageFormatProperties = (PFN_vkGetPhysicalDeviceImageFormatProperties) load(userptr, "vkGetPhysicalDeviceImageFormatProperties");
    glad_vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties) load(userptr, "vkGetPhysicalDeviceMemoryProperties");
    glad_vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties) load(userptr, "vkGetPhysicalDeviceProperties");
    glad_vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties) load(userptr, "vkGetPhysicalDeviceQueueFamilyProperties");
    glad_vkGetPhysicalDeviceSparseImageFormatProperties = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties) load(userptr, "vkGetPhysicalDeviceSparseImageFormatProperties");
    glad_vkGetPipelineCacheData = (PFN_vkGetPipelineCacheData) load(userptr, "vkGetPipelineCacheData");
    glad_vkGetQueryPoolResults = (PFN_vkGetQueryPoolResults) load(userptr, "vkGetQueryPoolResults");
    glad_vkGetRenderAreaGranularity = (PFN_vkGetRenderAreaGranularity) load(userptr, "vkGetRenderAreaGranularity");
    glad_vkInvalidateMappedMemoryRanges = (PFN_vkInvalidateMappedMemoryRanges) load(userptr, "vkInvalidateMappedMemoryRanges");
    glad_vkMapMemory = (PFN_vkMapMemory) load(userptr, "vkMapMemory");
    glad_vkMergePipelineCaches = (PFN_vkMergePipelineCaches) load(userptr, "vkMergePipelineCaches");
    glad_vkQueueBindSparse = (PFN_vkQueueBindSparse) load(userptr, "vkQueueBindSparse");
    glad_vkQueueSubmit = (PFN_vkQueueSubmit) load(userptr, "vkQueueSubmit");
    glad_vkQueueWaitIdle = (PFN_vkQueueWaitIdle) load(userptr, "vkQueueWaitIdle");
    glad_vkResetCommandBuffer = (PFN_vkResetCommandBuffer) load(userptr, "vkResetCommandBuffer");
    glad_vkResetCommandPool = (PFN_vkResetCommandPool) load(userptr, "vkResetCommandPool");
    glad_vkResetDescriptorPool = (PFN_vkResetDescriptorPool) load(userptr, "vkResetDescriptorPool");
    glad_vkResetEvent = (PFN_vkResetEvent) load(userptr, "vkResetEvent");
    glad_vkResetFences = (PFN_vkResetFences) load(userptr, "vkResetFences");
    glad_vkSetEvent = (PFN_vkSetEvent) load(userptr, "vkSetEvent");
    glad_vkUnmapMemory = (PFN_vkUnmapMemory) load(userptr, "vkUnmapMemory");
    glad_vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets) load(userptr, "vkUpdateDescriptorSets");
    glad_vkWaitForFences = (PFN_vkWaitForFences) load(userptr, "vkWaitForFences");
}
static void glad_vk_load_VK_VERSION_1_1( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_VERSION_1_1) return;
    glad_vkBindBufferMemory2 = (PFN_vkBindBufferMemory2) load(userptr, "vkBindBufferMemory2");
    glad_vkBindImageMemory2 = (PFN_vkBindImageMemory2) load(userptr, "vkBindImageMemory2");
    glad_vkCmdDispatchBase = (PFN_vkCmdDispatchBase) load(userptr, "vkCmdDispatchBase");
    glad_vkCmdSetDeviceMask = (PFN_vkCmdSetDeviceMask) load(userptr, "vkCmdSetDeviceMask");
    glad_vkCreateDescriptorUpdateTemplate = (PFN_vkCreateDescriptorUpdateTemplate) load(userptr, "vkCreateDescriptorUpdateTemplate");
    glad_vkCreateSamplerYcbcrConversion = (PFN_vkCreateSamplerYcbcrConversion) load(userptr, "vkCreateSamplerYcbcrConversion");
    glad_vkDestroyDescriptorUpdateTemplate = (PFN_vkDestroyDescriptorUpdateTemplate) load(userptr, "vkDestroyDescriptorUpdateTemplate");
    glad_vkDestroySamplerYcbcrConversion = (PFN_vkDestroySamplerYcbcrConversion) load(userptr, "vkDestroySamplerYcbcrConversion");
    glad_vkEnumerateInstanceVersion = (PFN_vkEnumerateInstanceVersion) load(userptr, "vkEnumerateInstanceVersion");
    glad_vkEnumeratePhysicalDeviceGroups = (PFN_vkEnumeratePhysicalDeviceGroups) load(userptr, "vkEnumeratePhysicalDeviceGroups");
    glad_vkGetBufferMemoryRequirements2 = (PFN_vkGetBufferMemoryRequirements2) load(userptr, "vkGetBufferMemoryRequirements2");
    glad_vkGetDescriptorSetLayoutSupport = (PFN_vkGetDescriptorSetLayoutSupport) load(userptr, "vkGetDescriptorSetLayoutSupport");
    glad_vkGetDeviceGroupPeerMemoryFeatures = (PFN_vkGetDeviceGroupPeerMemoryFeatures) load(userptr, "vkGetDeviceGroupPeerMemoryFeatures");
    glad_vkGetDeviceQueue2 = (PFN_vkGetDeviceQueue2) load(userptr, "vkGetDeviceQueue2");
    glad_vkGetImageMemoryRequirements2 = (PFN_vkGetImageMemoryRequirements2) load(userptr, "vkGetImageMemoryRequirements2");
    glad_vkGetImageSparseMemoryRequirements2 = (PFN_vkGetImageSparseMemoryRequirements2) load(userptr, "vkGetImageSparseMemoryRequirements2");
    glad_vkGetPhysicalDeviceExternalBufferProperties = (PFN_vkGetPhysicalDeviceExternalBufferProperties) load(userptr, "vkGetPhysicalDeviceExternalBufferProperties");
    glad_vkGetPhysicalDeviceExternalFenceProperties = (PFN_vkGetPhysicalDeviceExternalFenceProperties) load(userptr, "vkGetPhysicalDeviceExternalFenceProperties");
    glad_vkGetPhysicalDeviceExternalSemaphoreProperties = (PFN_vkGetPhysicalDeviceExternalSemaphoreProperties) load(userptr, "vkGetPhysicalDeviceExternalSemaphoreProperties");
    glad_vkGetPhysicalDeviceFeatures2 = (PFN_vkGetPhysicalDeviceFeatures2) load(userptr, "vkGetPhysicalDeviceFeatures2");
    glad_vkGetPhysicalDeviceFormatProperties2 = (PFN_vkGetPhysicalDeviceFormatProperties2) load(userptr, "vkGetPhysicalDeviceFormatProperties2");
    glad_vkGetPhysicalDeviceImageFormatProperties2 = (PFN_vkGetPhysicalDeviceImageFormatProperties2) load(userptr, "vkGetPhysicalDeviceImageFormatProperties2");
    glad_vkGetPhysicalDeviceMemoryProperties2 = (PFN_vkGetPhysicalDeviceMemoryProperties2) load(userptr, "vkGetPhysicalDeviceMemoryProperties2");
    glad_vkGetPhysicalDeviceProperties2 = (PFN_vkGetPhysicalDeviceProperties2) load(userptr, "vkGetPhysicalDeviceProperties2");
    glad_vkGetPhysicalDeviceQueueFamilyProperties2 = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2) load(userptr, "vkGetPhysicalDeviceQueueFamilyProperties2");
    glad_vkGetPhysicalDeviceSparseImageFormatProperties2 = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2) load(userptr, "vkGetPhysicalDeviceSparseImageFormatProperties2");
    glad_vkTrimCommandPool = (PFN_vkTrimCommandPool) load(userptr, "vkTrimCommandPool");
    glad_vkUpdateDescriptorSetWithTemplate = (PFN_vkUpdateDescriptorSetWithTemplate) load(userptr, "vkUpdateDescriptorSetWithTemplate");
}
static void glad_vk_load_VK_VERSION_1_2( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_VERSION_1_2) return;
    glad_vkCmdBeginRenderPass2 = (PFN_vkCmdBeginRenderPass2) load(userptr, "vkCmdBeginRenderPass2");
    glad_vkCmdDrawIndexedIndirectCount = (PFN_vkCmdDrawIndexedIndirectCount) load(userptr, "vkCmdDrawIndexedIndirectCount");
    glad_vkCmdDrawIndirectCount = (PFN_vkCmdDrawIndirectCount) load(userptr, "vkCmdDrawIndirectCount");
    glad_vkCmdEndRenderPass2 = (PFN_vkCmdEndRenderPass2) load(userptr, "vkCmdEndRenderPass2");
    glad_vkCmdNextSubpass2 = (PFN_vkCmdNextSubpass2) load(userptr, "vkCmdNextSubpass2");
    glad_vkCreateRenderPass2 = (PFN_vkCreateRenderPass2) load(userptr, "vkCreateRenderPass2");
    glad_vkGetBufferDeviceAddress = (PFN_vkGetBufferDeviceAddress) load(userptr, "vkGetBufferDeviceAddress");
    glad_vkGetBufferOpaqueCaptureAddress = (PFN_vkGetBufferOpaqueCaptureAddress) load(userptr, "vkGetBufferOpaqueCaptureAddress");
    glad_vkGetDeviceMemoryOpaqueCaptureAddress = (PFN_vkGetDeviceMemoryOpaqueCaptureAddress) load(userptr, "vkGetDeviceMemoryOpaqueCaptureAddress");
    glad_vkGetSemaphoreCounterValue = (PFN_vkGetSemaphoreCounterValue) load(userptr, "vkGetSemaphoreCounterValue");
    glad_vkResetQueryPool = (PFN_vkResetQueryPool) load(userptr, "vkResetQueryPool");
    glad_vkSignalSemaphore = (PFN_vkSignalSemaphore) load(userptr, "vkSignalSemaphore");
    glad_vkWaitSemaphores = (PFN_vkWaitSemaphores) load(userptr, "vkWaitSemaphores");
}
static void glad_vk_load_VK_VERSION_1_3( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_VERSION_1_3) return;
    glad_vkCmdBeginRendering = (PFN_vkCmdBeginRendering) load(userptr, "vkCmdBeginRendering");
    glad_vkCmdBindVertexBuffers2 = (PFN_vkCmdBindVertexBuffers2) load(userptr, "vkCmdBindVertexBuffers2");
    glad_vkCmdBlitImage2 = (PFN_vkCmdBlitImage2) load(userptr, "vkCmdBlitImage2");
    glad_vkCmdCopyBuffer2 = (PFN_vkCmdCopyBuffer2) load(userptr, "vkCmdCopyBuffer2");
    glad_vkCmdCopyBufferToImage2 = (PFN_vkCmdCopyBufferToImage2) load(userptr, "vkCmdCopyBufferToImage2");
    glad_vkCmdCopyImage2 = (PFN_vkCmdCopyImage2) load(userptr, "vkCmdCopyImage2");
    glad_vkCmdCopyImageToBuffer2 = (PFN_vkCmdCopyImageToBuffer2) load(userptr, "vkCmdCopyImageToBuffer2");
    glad_vkCmdEndRendering = (PFN_vkCmdEndRendering) load(userptr, "vkCmdEndRendering");
    glad_vkCmdPipelineBarrier2 = (PFN_vkCmdPipelineBarrier2) load(userptr, "vkCmdPipelineBarrier2");
    glad_vkCmdResetEvent2 = (PFN_vkCmdResetEvent2) load(userptr, "vkCmdResetEvent2");
    glad_vkCmdResolveImage2 = (PFN_vkCmdResolveImage2) load(userptr, "vkCmdResolveImage2");
    glad_vkCmdSetCullMode = (PFN_vkCmdSetCullMode) load(userptr, "vkCmdSetCullMode");
    glad_vkCmdSetDepthBiasEnable = (PFN_vkCmdSetDepthBiasEnable) load(userptr, "vkCmdSetDepthBiasEnable");
    glad_vkCmdSetDepthBoundsTestEnable = (PFN_vkCmdSetDepthBoundsTestEnable) load(userptr, "vkCmdSetDepthBoundsTestEnable");
    glad_vkCmdSetDepthCompareOp = (PFN_vkCmdSetDepthCompareOp) load(userptr, "vkCmdSetDepthCompareOp");
    glad_vkCmdSetDepthTestEnable = (PFN_vkCmdSetDepthTestEnable) load(userptr, "vkCmdSetDepthTestEnable");
    glad_vkCmdSetDepthWriteEnable = (PFN_vkCmdSetDepthWriteEnable) load(userptr, "vkCmdSetDepthWriteEnable");
    glad_vkCmdSetEvent2 = (PFN_vkCmdSetEvent2) load(userptr, "vkCmdSetEvent2");
    glad_vkCmdSetFrontFace = (PFN_vkCmdSetFrontFace) load(userptr, "vkCmdSetFrontFace");
    glad_vkCmdSetPrimitiveRestartEnable = (PFN_vkCmdSetPrimitiveRestartEnable) load(userptr, "vkCmdSetPrimitiveRestartEnable");
    glad_vkCmdSetPrimitiveTopology = (PFN_vkCmdSetPrimitiveTopology) load(userptr, "vkCmdSetPrimitiveTopology");
    glad_vkCmdSetRasterizerDiscardEnable = (PFN_vkCmdSetRasterizerDiscardEnable) load(userptr, "vkCmdSetRasterizerDiscardEnable");
    glad_vkCmdSetScissorWithCount = (PFN_vkCmdSetScissorWithCount) load(userptr, "vkCmdSetScissorWithCount");
    glad_vkCmdSetStencilOp = (PFN_vkCmdSetStencilOp) load(userptr, "vkCmdSetStencilOp");
    glad_vkCmdSetStencilTestEnable = (PFN_vkCmdSetStencilTestEnable) load(userptr, "vkCmdSetStencilTestEnable");
    glad_vkCmdSetViewportWithCount = (PFN_vkCmdSetViewportWithCount) load(userptr, "vkCmdSetViewportWithCount");
    glad_vkCmdWaitEvents2 = (PFN_vkCmdWaitEvents2) load(userptr, "vkCmdWaitEvents2");
    glad_vkCmdWriteTimestamp2 = (PFN_vkCmdWriteTimestamp2) load(userptr, "vkCmdWriteTimestamp2");
    glad_vkCreatePrivateDataSlot = (PFN_vkCreatePrivateDataSlot) load(userptr, "vkCreatePrivateDataSlot");
    glad_vkDestroyPrivateDataSlot = (PFN_vkDestroyPrivateDataSlot) load(userptr, "vkDestroyPrivateDataSlot");
    glad_vkGetDeviceBufferMemoryRequirements = (PFN_vkGetDeviceBufferMemoryRequirements) load(userptr, "vkGetDeviceBufferMemoryRequirements");
    glad_vkGetDeviceImageMemoryRequirements = (PFN_vkGetDeviceImageMemoryRequirements) load(userptr, "vkGetDeviceImageMemoryRequirements");
    glad_vkGetDeviceImageSparseMemoryRequirements = (PFN_vkGetDeviceImageSparseMemoryRequirements) load(userptr, "vkGetDeviceImageSparseMemoryRequirements");
    glad_vkGetPhysicalDeviceToolProperties = (PFN_vkGetPhysicalDeviceToolProperties) load(userptr, "vkGetPhysicalDeviceToolProperties");
    glad_vkGetPrivateData = (PFN_vkGetPrivateData) load(userptr, "vkGetPrivateData");
    glad_vkQueueSubmit2 = (PFN_vkQueueSubmit2) load(userptr, "vkQueueSubmit2");
    glad_vkSetPrivateData = (PFN_vkSetPrivateData) load(userptr, "vkSetPrivateData");
}
static void glad_vk_load_VK_VERSION_1_4( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_VERSION_1_4) return;
    glad_vkCmdBindDescriptorSets2 = (PFN_vkCmdBindDescriptorSets2) load(userptr, "vkCmdBindDescriptorSets2");
    glad_vkCmdBindIndexBuffer2 = (PFN_vkCmdBindIndexBuffer2) load(userptr, "vkCmdBindIndexBuffer2");
    glad_vkCmdPushConstants2 = (PFN_vkCmdPushConstants2) load(userptr, "vkCmdPushConstants2");
    glad_vkCmdPushDescriptorSet = (PFN_vkCmdPushDescriptorSet) load(userptr, "vkCmdPushDescriptorSet");
    glad_vkCmdPushDescriptorSet2 = (PFN_vkCmdPushDescriptorSet2) load(userptr, "vkCmdPushDescriptorSet2");
    glad_vkCmdPushDescriptorSetWithTemplate = (PFN_vkCmdPushDescriptorSetWithTemplate) load(userptr, "vkCmdPushDescriptorSetWithTemplate");
    glad_vkCmdPushDescriptorSetWithTemplate2 = (PFN_vkCmdPushDescriptorSetWithTemplate2) load(userptr, "vkCmdPushDescriptorSetWithTemplate2");
    glad_vkCmdSetLineStipple = (PFN_vkCmdSetLineStipple) load(userptr, "vkCmdSetLineStipple");
    glad_vkCmdSetRenderingAttachmentLocations = (PFN_vkCmdSetRenderingAttachmentLocations) load(userptr, "vkCmdSetRenderingAttachmentLocations");
    glad_vkCmdSetRenderingInputAttachmentIndices = (PFN_vkCmdSetRenderingInputAttachmentIndices) load(userptr, "vkCmdSetRenderingInputAttachmentIndices");
    glad_vkCopyImageToImage = (PFN_vkCopyImageToImage) load(userptr, "vkCopyImageToImage");
    glad_vkCopyImageToMemory = (PFN_vkCopyImageToMemory) load(userptr, "vkCopyImageToMemory");
    glad_vkCopyMemoryToImage = (PFN_vkCopyMemoryToImage) load(userptr, "vkCopyMemoryToImage");
    glad_vkGetDeviceImageSubresourceLayout = (PFN_vkGetDeviceImageSubresourceLayout) load(userptr, "vkGetDeviceImageSubresourceLayout");
    glad_vkGetImageSubresourceLayout2 = (PFN_vkGetImageSubresourceLayout2) load(userptr, "vkGetImageSubresourceLayout2");
    glad_vkGetRenderingAreaGranularity = (PFN_vkGetRenderingAreaGranularity) load(userptr, "vkGetRenderingAreaGranularity");
    glad_vkMapMemory2 = (PFN_vkMapMemory2) load(userptr, "vkMapMemory2");
    glad_vkTransitionImageLayout = (PFN_vkTransitionImageLayout) load(userptr, "vkTransitionImageLayout");
    glad_vkUnmapMemory2 = (PFN_vkUnmapMemory2) load(userptr, "vkUnmapMemory2");
}
static void glad_vk_load_VK_AMD_draw_indirect_count( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_AMD_draw_indirect_count) return;
    glad_vkCmdDrawIndexedIndirectCountAMD = (PFN_vkCmdDrawIndexedIndirectCountAMD) load(userptr, "vkCmdDrawIndexedIndirectCountAMD");
    glad_vkCmdDrawIndirectCountAMD = (PFN_vkCmdDrawIndirectCountAMD) load(userptr, "vkCmdDrawIndirectCountAMD");
}
static void glad_vk_load_VK_EXT_buffer_device_address( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_EXT_buffer_device_address) return;
    glad_vkGetBufferDeviceAddressEXT = (PFN_vkGetBufferDeviceAddressEXT) load(userptr, "vkGetBufferDeviceAddressEXT");
}
static void glad_vk_load_VK_EXT_extended_dynamic_state( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_EXT_extended_dynamic_state) return;
    glad_vkCmdBindVertexBuffers2EXT = (PFN_vkCmdBindVertexBuffers2EXT) load(userptr, "vkCmdBindVertexBuffers2EXT");
    glad_vkCmdSetCullModeEXT = (PFN_vkCmdSetCullModeEXT) load(userptr, "vkCmdSetCullModeEXT");
    glad_vkCmdSetDepthBoundsTestEnableEXT = (PFN_vkCmdSetDepthBoundsTestEnableEXT) load(userptr, "vkCmdSetDepthBoundsTestEnableEXT");
    glad_vkCmdSetDepthCompareOpEXT = (PFN_vkCmdSetDepthCompareOpEXT) load(userptr, "vkCmdSetDepthCompareOpEXT");
    glad_vkCmdSetDepthTestEnableEXT = (PFN_vkCmdSetDepthTestEnableEXT) load(userptr, "vkCmdSetDepthTestEnableEXT");
    glad_vkCmdSetDepthWriteEnableEXT = (PFN_vkCmdSetDepthWriteEnableEXT) load(userptr, "vkCmdSetDepthWriteEnableEXT");
    glad_vkCmdSetFrontFaceEXT = (PFN_vkCmdSetFrontFaceEXT) load(userptr, "vkCmdSetFrontFaceEXT");
    glad_vkCmdSetPrimitiveTopologyEXT = (PFN_vkCmdSetPrimitiveTopologyEXT) load(userptr, "vkCmdSetPrimitiveTopologyEXT");
    glad_vkCmdSetScissorWithCountEXT = (PFN_vkCmdSetScissorWithCountEXT) load(userptr, "vkCmdSetScissorWithCountEXT");
    glad_vkCmdSetStencilOpEXT = (PFN_vkCmdSetStencilOpEXT) load(userptr, "vkCmdSetStencilOpEXT");
    glad_vkCmdSetStencilTestEnableEXT = (PFN_vkCmdSetStencilTestEnableEXT) load(userptr, "vkCmdSetStencilTestEnableEXT");
    glad_vkCmdSetViewportWithCountEXT = (PFN_vkCmdSetViewportWithCountEXT) load(userptr, "vkCmdSetViewportWithCountEXT");
}
static void glad_vk_load_VK_EXT_extended_dynamic_state2( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_EXT_extended_dynamic_state2) return;
    glad_vkCmdSetDepthBiasEnableEXT = (PFN_vkCmdSetDepthBiasEnableEXT) load(userptr, "vkCmdSetDepthBiasEnableEXT");
    glad_vkCmdSetLogicOpEXT = (PFN_vkCmdSetLogicOpEXT) load(userptr, "vkCmdSetLogicOpEXT");
    glad_vkCmdSetPatchControlPointsEXT = (PFN_vkCmdSetPatchControlPointsEXT) load(userptr, "vkCmdSetPatchControlPointsEXT");
    glad_vkCmdSetPrimitiveRestartEnableEXT = (PFN_vkCmdSetPrimitiveRestartEnableEXT) load(userptr, "vkCmdSetPrimitiveRestartEnableEXT");
    glad_vkCmdSetRasterizerDiscardEnableEXT = (PFN_vkCmdSetRasterizerDiscardEnableEXT) load(userptr, "vkCmdSetRasterizerDiscardEnableEXT");
}
static void glad_vk_load_VK_EXT_host_image_copy( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_EXT_host_image_copy) return;
    glad_vkCopyImageToImageEXT = (PFN_vkCopyImageToImageEXT) load(userptr, "vkCopyImageToImageEXT");
    glad_vkCopyImageToMemoryEXT = (PFN_vkCopyImageToMemoryEXT) load(userptr, "vkCopyImageToMemoryEXT");
    glad_vkCopyMemoryToImageEXT = (PFN_vkCopyMemoryToImageEXT) load(userptr, "vkCopyMemoryToImageEXT");
    glad_vkGetImageSubresourceLayout2EXT = (PFN_vkGetImageSubresourceLayout2EXT) load(userptr, "vkGetImageSubresourceLayout2EXT");
    glad_vkTransitionImageLayoutEXT = (PFN_vkTransitionImageLayoutEXT) load(userptr, "vkTransitionImageLayoutEXT");
}
static void glad_vk_load_VK_EXT_host_query_reset( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_EXT_host_query_reset) return;
    glad_vkResetQueryPoolEXT = (PFN_vkResetQueryPoolEXT) load(userptr, "vkResetQueryPoolEXT");
}
static void glad_vk_load_VK_EXT_image_compression_control( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_EXT_image_compression_control) return;
    glad_vkGetImageSubresourceLayout2EXT = (PFN_vkGetImageSubresourceLayout2EXT) load(userptr, "vkGetImageSubresourceLayout2EXT");
}
static void glad_vk_load_VK_EXT_line_rasterization( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_EXT_line_rasterization) return;
    glad_vkCmdSetLineStippleEXT = (PFN_vkCmdSetLineStippleEXT) load(userptr, "vkCmdSetLineStippleEXT");
}
static void glad_vk_load_VK_EXT_private_data( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_EXT_private_data) return;
    glad_vkCreatePrivateDataSlotEXT = (PFN_vkCreatePrivateDataSlotEXT) load(userptr, "vkCreatePrivateDataSlotEXT");
    glad_vkDestroyPrivateDataSlotEXT = (PFN_vkDestroyPrivateDataSlotEXT) load(userptr, "vkDestroyPrivateDataSlotEXT");
    glad_vkGetPrivateDataEXT = (PFN_vkGetPrivateDataEXT) load(userptr, "vkGetPrivateDataEXT");
    glad_vkSetPrivateDataEXT = (PFN_vkSetPrivateDataEXT) load(userptr, "vkSetPrivateDataEXT");
}
static void glad_vk_load_VK_EXT_shader_object( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_EXT_shader_object) return;
    glad_vkCmdBindShadersEXT = (PFN_vkCmdBindShadersEXT) load(userptr, "vkCmdBindShadersEXT");
    glad_vkCmdBindVertexBuffers2EXT = (PFN_vkCmdBindVertexBuffers2EXT) load(userptr, "vkCmdBindVertexBuffers2EXT");
    glad_vkCmdSetAlphaToCoverageEnableEXT = (PFN_vkCmdSetAlphaToCoverageEnableEXT) load(userptr, "vkCmdSetAlphaToCoverageEnableEXT");
    glad_vkCmdSetAlphaToOneEnableEXT = (PFN_vkCmdSetAlphaToOneEnableEXT) load(userptr, "vkCmdSetAlphaToOneEnableEXT");
    glad_vkCmdSetColorBlendAdvancedEXT = (PFN_vkCmdSetColorBlendAdvancedEXT) load(userptr, "vkCmdSetColorBlendAdvancedEXT");
    glad_vkCmdSetColorBlendEnableEXT = (PFN_vkCmdSetColorBlendEnableEXT) load(userptr, "vkCmdSetColorBlendEnableEXT");
    glad_vkCmdSetColorBlendEquationEXT = (PFN_vkCmdSetColorBlendEquationEXT) load(userptr, "vkCmdSetColorBlendEquationEXT");
    glad_vkCmdSetColorWriteMaskEXT = (PFN_vkCmdSetColorWriteMaskEXT) load(userptr, "vkCmdSetColorWriteMaskEXT");
    glad_vkCmdSetConservativeRasterizationModeEXT = (PFN_vkCmdSetConservativeRasterizationModeEXT) load(userptr, "vkCmdSetConservativeRasterizationModeEXT");
    glad_vkCmdSetCoverageModulationModeNV = (PFN_vkCmdSetCoverageModulationModeNV) load(userptr, "vkCmdSetCoverageModulationModeNV");
    glad_vkCmdSetCoverageModulationTableEnableNV = (PFN_vkCmdSetCoverageModulationTableEnableNV) load(userptr, "vkCmdSetCoverageModulationTableEnableNV");
    glad_vkCmdSetCoverageModulationTableNV = (PFN_vkCmdSetCoverageModulationTableNV) load(userptr, "vkCmdSetCoverageModulationTableNV");
    glad_vkCmdSetCoverageReductionModeNV = (PFN_vkCmdSetCoverageReductionModeNV) load(userptr, "vkCmdSetCoverageReductionModeNV");
    glad_vkCmdSetCoverageToColorEnableNV = (PFN_vkCmdSetCoverageToColorEnableNV) load(userptr, "vkCmdSetCoverageToColorEnableNV");
    glad_vkCmdSetCoverageToColorLocationNV = (PFN_vkCmdSetCoverageToColorLocationNV) load(userptr, "vkCmdSetCoverageToColorLocationNV");
    glad_vkCmdSetCullModeEXT = (PFN_vkCmdSetCullModeEXT) load(userptr, "vkCmdSetCullModeEXT");
    glad_vkCmdSetDepthBiasEnableEXT = (PFN_vkCmdSetDepthBiasEnableEXT) load(userptr, "vkCmdSetDepthBiasEnableEXT");
    glad_vkCmdSetDepthBoundsTestEnableEXT = (PFN_vkCmdSetDepthBoundsTestEnableEXT) load(userptr, "vkCmdSetDepthBoundsTestEnableEXT");
    glad_vkCmdSetDepthClampEnableEXT = (PFN_vkCmdSetDepthClampEnableEXT) load(userptr, "vkCmdSetDepthClampEnableEXT");
    glad_vkCmdSetDepthClampRangeEXT = (PFN_vkCmdSetDepthClampRangeEXT) load(userptr, "vkCmdSetDepthClampRangeEXT");
    glad_vkCmdSetDepthClipEnableEXT = (PFN_vkCmdSetDepthClipEnableEXT) load(userptr, "vkCmdSetDepthClipEnableEXT");
    glad_vkCmdSetDepthClipNegativeOneToOneEXT = (PFN_vkCmdSetDepthClipNegativeOneToOneEXT) load(userptr, "vkCmdSetDepthClipNegativeOneToOneEXT");
    glad_vkCmdSetDepthCompareOpEXT = (PFN_vkCmdSetDepthCompareOpEXT) load(userptr, "vkCmdSetDepthCompareOpEXT");
    glad_vkCmdSetDepthTestEnableEXT = (PFN_vkCmdSetDepthTestEnableEXT) load(userptr, "vkCmdSetDepthTestEnableEXT");
    glad_vkCmdSetDepthWriteEnableEXT = (PFN_vkCmdSetDepthWriteEnableEXT) load(userptr, "vkCmdSetDepthWriteEnableEXT");
    glad_vkCmdSetExtraPrimitiveOverestimationSizeEXT = (PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT) load(userptr, "vkCmdSetExtraPrimitiveOverestimationSizeEXT");
    glad_vkCmdSetFrontFaceEXT = (PFN_vkCmdSetFrontFaceEXT) load(userptr, "vkCmdSetFrontFaceEXT");
    glad_vkCmdSetLineRasterizationModeEXT = (PFN_vkCmdSetLineRasterizationModeEXT) load(userptr, "vkCmdSetLineRasterizationModeEXT");
    glad_vkCmdSetLineStippleEnableEXT = (PFN_vkCmdSetLineStippleEnableEXT) load(userptr, "vkCmdSetLineStippleEnableEXT");
    glad_vkCmdSetLogicOpEXT = (PFN_vkCmdSetLogicOpEXT) load(userptr, "vkCmdSetLogicOpEXT");
    glad_vkCmdSetLogicOpEnableEXT = (PFN_vkCmdSetLogicOpEnableEXT) load(userptr, "vkCmdSetLogicOpEnableEXT");
    glad_vkCmdSetPatchControlPointsEXT = (PFN_vkCmdSetPatchControlPointsEXT) load(userptr, "vkCmdSetPatchControlPointsEXT");
    glad_vkCmdSetPolygonModeEXT = (PFN_vkCmdSetPolygonModeEXT) load(userptr, "vkCmdSetPolygonModeEXT");
    glad_vkCmdSetPrimitiveRestartEnableEXT = (PFN_vkCmdSetPrimitiveRestartEnableEXT) load(userptr, "vkCmdSetPrimitiveRestartEnableEXT");
    glad_vkCmdSetPrimitiveTopologyEXT = (PFN_vkCmdSetPrimitiveTopologyEXT) load(userptr, "vkCmdSetPrimitiveTopologyEXT");
    glad_vkCmdSetProvokingVertexModeEXT = (PFN_vkCmdSetProvokingVertexModeEXT) load(userptr, "vkCmdSetProvokingVertexModeEXT");
    glad_vkCmdSetRasterizationSamplesEXT = (PFN_vkCmdSetRasterizationSamplesEXT) load(userptr, "vkCmdSetRasterizationSamplesEXT");
    glad_vkCmdSetRasterizationStreamEXT = (PFN_vkCmdSetRasterizationStreamEXT) load(userptr, "vkCmdSetRasterizationStreamEXT");
    glad_vkCmdSetRasterizerDiscardEnableEXT = (PFN_vkCmdSetRasterizerDiscardEnableEXT) load(userptr, "vkCmdSetRasterizerDiscardEnableEXT");
    glad_vkCmdSetRepresentativeFragmentTestEnableNV = (PFN_vkCmdSetRepresentativeFragmentTestEnableNV) load(userptr, "vkCmdSetRepresentativeFragmentTestEnableNV");
    glad_vkCmdSetSampleLocationsEnableEXT = (PFN_vkCmdSetSampleLocationsEnableEXT) load(userptr, "vkCmdSetSampleLocationsEnableEXT");
    glad_vkCmdSetSampleMaskEXT = (PFN_vkCmdSetSampleMaskEXT) load(userptr, "vkCmdSetSampleMaskEXT");
    glad_vkCmdSetScissorWithCountEXT = (PFN_vkCmdSetScissorWithCountEXT) load(userptr, "vkCmdSetScissorWithCountEXT");
    glad_vkCmdSetShadingRateImageEnableNV = (PFN_vkCmdSetShadingRateImageEnableNV) load(userptr, "vkCmdSetShadingRateImageEnableNV");
    glad_vkCmdSetStencilOpEXT = (PFN_vkCmdSetStencilOpEXT) load(userptr, "vkCmdSetStencilOpEXT");
    glad_vkCmdSetStencilTestEnableEXT = (PFN_vkCmdSetStencilTestEnableEXT) load(userptr, "vkCmdSetStencilTestEnableEXT");
    glad_vkCmdSetTessellationDomainOriginEXT = (PFN_vkCmdSetTessellationDomainOriginEXT) load(userptr, "vkCmdSetTessellationDomainOriginEXT");
    glad_vkCmdSetVertexInputEXT = (PFN_vkCmdSetVertexInputEXT) load(userptr, "vkCmdSetVertexInputEXT");
    glad_vkCmdSetViewportSwizzleNV = (PFN_vkCmdSetViewportSwizzleNV) load(userptr, "vkCmdSetViewportSwizzleNV");
    glad_vkCmdSetViewportWScalingEnableNV = (PFN_vkCmdSetViewportWScalingEnableNV) load(userptr, "vkCmdSetViewportWScalingEnableNV");
    glad_vkCmdSetViewportWithCountEXT = (PFN_vkCmdSetViewportWithCountEXT) load(userptr, "vkCmdSetViewportWithCountEXT");
    glad_vkCreateShadersEXT = (PFN_vkCreateShadersEXT) load(userptr, "vkCreateShadersEXT");
    glad_vkDestroyShaderEXT = (PFN_vkDestroyShaderEXT) load(userptr, "vkDestroyShaderEXT");
    glad_vkGetShaderBinaryDataEXT = (PFN_vkGetShaderBinaryDataEXT) load(userptr, "vkGetShaderBinaryDataEXT");
}
static void glad_vk_load_VK_EXT_tooling_info( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_EXT_tooling_info) return;
    glad_vkGetPhysicalDeviceToolPropertiesEXT = (PFN_vkGetPhysicalDeviceToolPropertiesEXT) load(userptr, "vkGetPhysicalDeviceToolPropertiesEXT");
}
static void glad_vk_load_VK_KHR_bind_memory2( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_bind_memory2) return;
    glad_vkBindBufferMemory2KHR = (PFN_vkBindBufferMemory2KHR) load(userptr, "vkBindBufferMemory2KHR");
    glad_vkBindImageMemory2KHR = (PFN_vkBindImageMemory2KHR) load(userptr, "vkBindImageMemory2KHR");
}
static void glad_vk_load_VK_KHR_buffer_device_address( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_buffer_device_address) return;
    glad_vkGetBufferDeviceAddressKHR = (PFN_vkGetBufferDeviceAddressKHR) load(userptr, "vkGetBufferDeviceAddressKHR");
    glad_vkGetBufferOpaqueCaptureAddressKHR = (PFN_vkGetBufferOpaqueCaptureAddressKHR) load(userptr, "vkGetBufferOpaqueCaptureAddressKHR");
    glad_vkGetDeviceMemoryOpaqueCaptureAddressKHR = (PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR) load(userptr, "vkGetDeviceMemoryOpaqueCaptureAddressKHR");
}
static void glad_vk_load_VK_KHR_copy_commands2( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_copy_commands2) return;
    glad_vkCmdBlitImage2KHR = (PFN_vkCmdBlitImage2KHR) load(userptr, "vkCmdBlitImage2KHR");
    glad_vkCmdCopyBuffer2KHR = (PFN_vkCmdCopyBuffer2KHR) load(userptr, "vkCmdCopyBuffer2KHR");
    glad_vkCmdCopyBufferToImage2KHR = (PFN_vkCmdCopyBufferToImage2KHR) load(userptr, "vkCmdCopyBufferToImage2KHR");
    glad_vkCmdCopyImage2KHR = (PFN_vkCmdCopyImage2KHR) load(userptr, "vkCmdCopyImage2KHR");
    glad_vkCmdCopyImageToBuffer2KHR = (PFN_vkCmdCopyImageToBuffer2KHR) load(userptr, "vkCmdCopyImageToBuffer2KHR");
    glad_vkCmdResolveImage2KHR = (PFN_vkCmdResolveImage2KHR) load(userptr, "vkCmdResolveImage2KHR");
}
static void glad_vk_load_VK_KHR_create_renderpass2( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_create_renderpass2) return;
    glad_vkCmdBeginRenderPass2KHR = (PFN_vkCmdBeginRenderPass2KHR) load(userptr, "vkCmdBeginRenderPass2KHR");
    glad_vkCmdEndRenderPass2KHR = (PFN_vkCmdEndRenderPass2KHR) load(userptr, "vkCmdEndRenderPass2KHR");
    glad_vkCmdNextSubpass2KHR = (PFN_vkCmdNextSubpass2KHR) load(userptr, "vkCmdNextSubpass2KHR");
    glad_vkCreateRenderPass2KHR = (PFN_vkCreateRenderPass2KHR) load(userptr, "vkCreateRenderPass2KHR");
}
static void glad_vk_load_VK_KHR_descriptor_update_template( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_descriptor_update_template) return;
    glad_vkCmdPushDescriptorSetWithTemplateKHR = (PFN_vkCmdPushDescriptorSetWithTemplateKHR) load(userptr, "vkCmdPushDescriptorSetWithTemplateKHR");
    glad_vkCreateDescriptorUpdateTemplateKHR = (PFN_vkCreateDescriptorUpdateTemplateKHR) load(userptr, "vkCreateDescriptorUpdateTemplateKHR");
    glad_vkDestroyDescriptorUpdateTemplateKHR = (PFN_vkDestroyDescriptorUpdateTemplateKHR) load(userptr, "vkDestroyDescriptorUpdateTemplateKHR");
    glad_vkUpdateDescriptorSetWithTemplateKHR = (PFN_vkUpdateDescriptorSetWithTemplateKHR) load(userptr, "vkUpdateDescriptorSetWithTemplateKHR");
}
static void glad_vk_load_VK_KHR_device_group( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_device_group) return;
    glad_vkAcquireNextImage2KHR = (PFN_vkAcquireNextImage2KHR) load(userptr, "vkAcquireNextImage2KHR");
    glad_vkCmdDispatchBaseKHR = (PFN_vkCmdDispatchBaseKHR) load(userptr, "vkCmdDispatchBaseKHR");
    glad_vkCmdSetDeviceMaskKHR = (PFN_vkCmdSetDeviceMaskKHR) load(userptr, "vkCmdSetDeviceMaskKHR");
    glad_vkGetDeviceGroupPeerMemoryFeaturesKHR = (PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR) load(userptr, "vkGetDeviceGroupPeerMemoryFeaturesKHR");
    glad_vkGetDeviceGroupPresentCapabilitiesKHR = (PFN_vkGetDeviceGroupPresentCapabilitiesKHR) load(userptr, "vkGetDeviceGroupPresentCapabilitiesKHR");
    glad_vkGetDeviceGroupSurfacePresentModesKHR = (PFN_vkGetDeviceGroupSurfacePresentModesKHR) load(userptr, "vkGetDeviceGroupSurfacePresentModesKHR");
    glad_vkGetPhysicalDevicePresentRectanglesKHR = (PFN_vkGetPhysicalDevicePresentRectanglesKHR) load(userptr, "vkGetPhysicalDevicePresentRectanglesKHR");
}
static void glad_vk_load_VK_KHR_device_group_creation( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_device_group_creation) return;
    glad_vkEnumeratePhysicalDeviceGroupsKHR = (PFN_vkEnumeratePhysicalDeviceGroupsKHR) load(userptr, "vkEnumeratePhysicalDeviceGroupsKHR");
}
static void glad_vk_load_VK_KHR_draw_indirect_count( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_draw_indirect_count) return;
    glad_vkCmdDrawIndexedIndirectCountKHR = (PFN_vkCmdDrawIndexedIndirectCountKHR) load(userptr, "vkCmdDrawIndexedIndirectCountKHR");
    glad_vkCmdDrawIndirectCountKHR = (PFN_vkCmdDrawIndirectCountKHR) load(userptr, "vkCmdDrawIndirectCountKHR");
}
static void glad_vk_load_VK_KHR_dynamic_rendering( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_dynamic_rendering) return;
    glad_vkCmdBeginRenderingKHR = (PFN_vkCmdBeginRenderingKHR) load(userptr, "vkCmdBeginRenderingKHR");
    glad_vkCmdEndRenderingKHR = (PFN_vkCmdEndRenderingKHR) load(userptr, "vkCmdEndRenderingKHR");
}
static void glad_vk_load_VK_KHR_dynamic_rendering_local_read( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_dynamic_rendering_local_read) return;
    glad_vkCmdSetRenderingAttachmentLocationsKHR = (PFN_vkCmdSetRenderingAttachmentLocationsKHR) load(userptr, "vkCmdSetRenderingAttachmentLocationsKHR");
    glad_vkCmdSetRenderingInputAttachmentIndicesKHR = (PFN_vkCmdSetRenderingInputAttachmentIndicesKHR) load(userptr, "vkCmdSetRenderingInputAttachmentIndicesKHR");
}
static void glad_vk_load_VK_KHR_external_fence_capabilities( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_external_fence_capabilities) return;
    glad_vkGetPhysicalDeviceExternalFencePropertiesKHR = (PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR) load(userptr, "vkGetPhysicalDeviceExternalFencePropertiesKHR");
}
static void glad_vk_load_VK_KHR_external_memory_capabilities( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_external_memory_capabilities) return;
    glad_vkGetPhysicalDeviceExternalBufferPropertiesKHR = (PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR) load(userptr, "vkGetPhysicalDeviceExternalBufferPropertiesKHR");
}
static void glad_vk_load_VK_KHR_external_semaphore_capabilities( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_external_semaphore_capabilities) return;
    glad_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = (PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR) load(userptr, "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR");
}
static void glad_vk_load_VK_KHR_get_memory_requirements2( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_get_memory_requirements2) return;
    glad_vkGetBufferMemoryRequirements2KHR = (PFN_vkGetBufferMemoryRequirements2KHR) load(userptr, "vkGetBufferMemoryRequirements2KHR");
    glad_vkGetImageMemoryRequirements2KHR = (PFN_vkGetImageMemoryRequirements2KHR) load(userptr, "vkGetImageMemoryRequirements2KHR");
    glad_vkGetImageSparseMemoryRequirements2KHR = (PFN_vkGetImageSparseMemoryRequirements2KHR) load(userptr, "vkGetImageSparseMemoryRequirements2KHR");
}
static void glad_vk_load_VK_KHR_get_physical_device_properties2( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_get_physical_device_properties2) return;
    glad_vkGetPhysicalDeviceFeatures2KHR = (PFN_vkGetPhysicalDeviceFeatures2KHR) load(userptr, "vkGetPhysicalDeviceFeatures2KHR");
    glad_vkGetPhysicalDeviceFormatProperties2KHR = (PFN_vkGetPhysicalDeviceFormatProperties2KHR) load(userptr, "vkGetPhysicalDeviceFormatProperties2KHR");
    glad_vkGetPhysicalDeviceImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceImageFormatProperties2KHR) load(userptr, "vkGetPhysicalDeviceImageFormatProperties2KHR");
    glad_vkGetPhysicalDeviceMemoryProperties2KHR = (PFN_vkGetPhysicalDeviceMemoryProperties2KHR) load(userptr, "vkGetPhysicalDeviceMemoryProperties2KHR");
    glad_vkGetPhysicalDeviceProperties2KHR = (PFN_vkGetPhysicalDeviceProperties2KHR) load(userptr, "vkGetPhysicalDeviceProperties2KHR");
    glad_vkGetPhysicalDeviceQueueFamilyProperties2KHR = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR) load(userptr, "vkGetPhysicalDeviceQueueFamilyProperties2KHR");
    glad_vkGetPhysicalDeviceSparseImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR) load(userptr, "vkGetPhysicalDeviceSparseImageFormatProperties2KHR");
}
static void glad_vk_load_VK_KHR_line_rasterization( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_line_rasterization) return;
    glad_vkCmdSetLineStippleKHR = (PFN_vkCmdSetLineStippleKHR) load(userptr, "vkCmdSetLineStippleKHR");
}
static void glad_vk_load_VK_KHR_maintenance1( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_maintenance1) return;
    glad_vkTrimCommandPoolKHR = (PFN_vkTrimCommandPoolKHR) load(userptr, "vkTrimCommandPoolKHR");
}
static void glad_vk_load_VK_KHR_maintenance3( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_maintenance3) return;
    glad_vkGetDescriptorSetLayoutSupportKHR = (PFN_vkGetDescriptorSetLayoutSupportKHR) load(userptr, "vkGetDescriptorSetLayoutSupportKHR");
}
static void glad_vk_load_VK_KHR_maintenance4( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_maintenance4) return;
    glad_vkGetDeviceBufferMemoryRequirementsKHR = (PFN_vkGetDeviceBufferMemoryRequirementsKHR) load(userptr, "vkGetDeviceBufferMemoryRequirementsKHR");
    glad_vkGetDeviceImageMemoryRequirementsKHR = (PFN_vkGetDeviceImageMemoryRequirementsKHR) load(userptr, "vkGetDeviceImageMemoryRequirementsKHR");
    glad_vkGetDeviceImageSparseMemoryRequirementsKHR = (PFN_vkGetDeviceImageSparseMemoryRequirementsKHR) load(userptr, "vkGetDeviceImageSparseMemoryRequirementsKHR");
}
static void glad_vk_load_VK_KHR_maintenance5( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_maintenance5) return;
    glad_vkCmdBindIndexBuffer2KHR = (PFN_vkCmdBindIndexBuffer2KHR) load(userptr, "vkCmdBindIndexBuffer2KHR");
    glad_vkGetDeviceImageSubresourceLayoutKHR = (PFN_vkGetDeviceImageSubresourceLayoutKHR) load(userptr, "vkGetDeviceImageSubresourceLayoutKHR");
    glad_vkGetImageSubresourceLayout2KHR = (PFN_vkGetImageSubresourceLayout2KHR) load(userptr, "vkGetImageSubresourceLayout2KHR");
    glad_vkGetRenderingAreaGranularityKHR = (PFN_vkGetRenderingAreaGranularityKHR) load(userptr, "vkGetRenderingAreaGranularityKHR");
}
static void glad_vk_load_VK_KHR_maintenance6( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_maintenance6) return;
    glad_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT = (PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT) load(userptr, "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT");
    glad_vkCmdBindDescriptorSets2KHR = (PFN_vkCmdBindDescriptorSets2KHR) load(userptr, "vkCmdBindDescriptorSets2KHR");
    glad_vkCmdPushConstants2KHR = (PFN_vkCmdPushConstants2KHR) load(userptr, "vkCmdPushConstants2KHR");
    glad_vkCmdPushDescriptorSet2KHR = (PFN_vkCmdPushDescriptorSet2KHR) load(userptr, "vkCmdPushDescriptorSet2KHR");
    glad_vkCmdPushDescriptorSetWithTemplate2KHR = (PFN_vkCmdPushDescriptorSetWithTemplate2KHR) load(userptr, "vkCmdPushDescriptorSetWithTemplate2KHR");
    glad_vkCmdSetDescriptorBufferOffsets2EXT = (PFN_vkCmdSetDescriptorBufferOffsets2EXT) load(userptr, "vkCmdSetDescriptorBufferOffsets2EXT");
}
static void glad_vk_load_VK_KHR_map_memory2( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_map_memory2) return;
    glad_vkMapMemory2KHR = (PFN_vkMapMemory2KHR) load(userptr, "vkMapMemory2KHR");
    glad_vkUnmapMemory2KHR = (PFN_vkUnmapMemory2KHR) load(userptr, "vkUnmapMemory2KHR");
}
static void glad_vk_load_VK_KHR_push_descriptor( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_push_descriptor) return;
    glad_vkCmdPushDescriptorSetKHR = (PFN_vkCmdPushDescriptorSetKHR) load(userptr, "vkCmdPushDescriptorSetKHR");
    glad_vkCmdPushDescriptorSetWithTemplateKHR = (PFN_vkCmdPushDescriptorSetWithTemplateKHR) load(userptr, "vkCmdPushDescriptorSetWithTemplateKHR");
}
static void glad_vk_load_VK_KHR_sampler_ycbcr_conversion( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_sampler_ycbcr_conversion) return;
    glad_vkCreateSamplerYcbcrConversionKHR = (PFN_vkCreateSamplerYcbcrConversionKHR) load(userptr, "vkCreateSamplerYcbcrConversionKHR");
    glad_vkDestroySamplerYcbcrConversionKHR = (PFN_vkDestroySamplerYcbcrConversionKHR) load(userptr, "vkDestroySamplerYcbcrConversionKHR");
}
static void glad_vk_load_VK_KHR_synchronization2( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_synchronization2) return;
    glad_vkCmdPipelineBarrier2KHR = (PFN_vkCmdPipelineBarrier2KHR) load(userptr, "vkCmdPipelineBarrier2KHR");
    glad_vkCmdResetEvent2KHR = (PFN_vkCmdResetEvent2KHR) load(userptr, "vkCmdResetEvent2KHR");
    glad_vkCmdSetEvent2KHR = (PFN_vkCmdSetEvent2KHR) load(userptr, "vkCmdSetEvent2KHR");
    glad_vkCmdWaitEvents2KHR = (PFN_vkCmdWaitEvents2KHR) load(userptr, "vkCmdWaitEvents2KHR");
    glad_vkCmdWriteTimestamp2KHR = (PFN_vkCmdWriteTimestamp2KHR) load(userptr, "vkCmdWriteTimestamp2KHR");
    glad_vkQueueSubmit2KHR = (PFN_vkQueueSubmit2KHR) load(userptr, "vkQueueSubmit2KHR");
}
static void glad_vk_load_VK_KHR_timeline_semaphore( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_VK_KHR_timeline_semaphore) return;
    glad_vkGetSemaphoreCounterValueKHR = (PFN_vkGetSemaphoreCounterValueKHR) load(userptr, "vkGetSemaphoreCounterValueKHR");
    glad_vkSignalSemaphoreKHR = (PFN_vkSignalSemaphoreKHR) load(userptr, "vkSignalSemaphoreKHR");
    glad_vkWaitSemaphoresKHR = (PFN_vkWaitSemaphoresKHR) load(userptr, "vkWaitSemaphoresKHR");
}


static void glad_vk_resolve_aliases(void) {
    if (glad_vkBindBufferMemory2 == NULL && glad_vkBindBufferMemory2KHR != NULL) glad_vkBindBufferMemory2 = (PFN_vkBindBufferMemory2)glad_vkBindBufferMemory2KHR;
    if (glad_vkBindBufferMemory2KHR == NULL && glad_vkBindBufferMemory2 != NULL) glad_vkBindBufferMemory2KHR = (PFN_vkBindBufferMemory2KHR)glad_vkBindBufferMemory2;
    if (glad_vkBindImageMemory2 == NULL && glad_vkBindImageMemory2KHR != NULL) glad_vkBindImageMemory2 = (PFN_vkBindImageMemory2)glad_vkBindImageMemory2KHR;
    if (glad_vkBindImageMemory2KHR == NULL && glad_vkBindImageMemory2 != NULL) glad_vkBindImageMemory2KHR = (PFN_vkBindImageMemory2KHR)glad_vkBindImageMemory2;
    if (glad_vkCmdBeginRendering == NULL && glad_vkCmdBeginRenderingKHR != NULL) glad_vkCmdBeginRendering = (PFN_vkCmdBeginRendering)glad_vkCmdBeginRenderingKHR;
    if (glad_vkCmdBeginRenderingKHR == NULL && glad_vkCmdBeginRendering != NULL) glad_vkCmdBeginRenderingKHR = (PFN_vkCmdBeginRenderingKHR)glad_vkCmdBeginRendering;
    if (glad_vkCmdBeginRenderPass2 == NULL && glad_vkCmdBeginRenderPass2KHR != NULL) glad_vkCmdBeginRenderPass2 = (PFN_vkCmdBeginRenderPass2)glad_vkCmdBeginRenderPass2KHR;
    if (glad_vkCmdBeginRenderPass2KHR == NULL && glad_vkCmdBeginRenderPass2 != NULL) glad_vkCmdBeginRenderPass2KHR = (PFN_vkCmdBeginRenderPass2KHR)glad_vkCmdBeginRenderPass2;
    if (glad_vkCmdBindDescriptorSets2 == NULL && glad_vkCmdBindDescriptorSets2KHR != NULL) glad_vkCmdBindDescriptorSets2 = (PFN_vkCmdBindDescriptorSets2)glad_vkCmdBindDescriptorSets2KHR;
    if (glad_vkCmdBindDescriptorSets2KHR == NULL && glad_vkCmdBindDescriptorSets2 != NULL) glad_vkCmdBindDescriptorSets2KHR = (PFN_vkCmdBindDescriptorSets2KHR)glad_vkCmdBindDescriptorSets2;
    if (glad_vkCmdBindIndexBuffer2 == NULL && glad_vkCmdBindIndexBuffer2KHR != NULL) glad_vkCmdBindIndexBuffer2 = (PFN_vkCmdBindIndexBuffer2)glad_vkCmdBindIndexBuffer2KHR;
    if (glad_vkCmdBindIndexBuffer2KHR == NULL && glad_vkCmdBindIndexBuffer2 != NULL) glad_vkCmdBindIndexBuffer2KHR = (PFN_vkCmdBindIndexBuffer2KHR)glad_vkCmdBindIndexBuffer2;
    if (glad_vkCmdBindVertexBuffers2 == NULL && glad_vkCmdBindVertexBuffers2EXT != NULL) glad_vkCmdBindVertexBuffers2 = (PFN_vkCmdBindVertexBuffers2)glad_vkCmdBindVertexBuffers2EXT;
    if (glad_vkCmdBindVertexBuffers2EXT == NULL && glad_vkCmdBindVertexBuffers2 != NULL) glad_vkCmdBindVertexBuffers2EXT = (PFN_vkCmdBindVertexBuffers2EXT)glad_vkCmdBindVertexBuffers2;
    if (glad_vkCmdBlitImage2 == NULL && glad_vkCmdBlitImage2KHR != NULL) glad_vkCmdBlitImage2 = (PFN_vkCmdBlitImage2)glad_vkCmdBlitImage2KHR;
    if (glad_vkCmdBlitImage2KHR == NULL && glad_vkCmdBlitImage2 != NULL) glad_vkCmdBlitImage2KHR = (PFN_vkCmdBlitImage2KHR)glad_vkCmdBlitImage2;
    if (glad_vkCmdCopyBuffer2 == NULL && glad_vkCmdCopyBuffer2KHR != NULL) glad_vkCmdCopyBuffer2 = (PFN_vkCmdCopyBuffer2)glad_vkCmdCopyBuffer2KHR;
    if (glad_vkCmdCopyBuffer2KHR == NULL && glad_vkCmdCopyBuffer2 != NULL) glad_vkCmdCopyBuffer2KHR = (PFN_vkCmdCopyBuffer2KHR)glad_vkCmdCopyBuffer2;
    if (glad_vkCmdCopyBufferToImage2 == NULL && glad_vkCmdCopyBufferToImage2KHR != NULL) glad_vkCmdCopyBufferToImage2 = (PFN_vkCmdCopyBufferToImage2)glad_vkCmdCopyBufferToImage2KHR;
    if (glad_vkCmdCopyBufferToImage2KHR == NULL && glad_vkCmdCopyBufferToImage2 != NULL) glad_vkCmdCopyBufferToImage2KHR = (PFN_vkCmdCopyBufferToImage2KHR)glad_vkCmdCopyBufferToImage2;
    if (glad_vkCmdCopyImage2 == NULL && glad_vkCmdCopyImage2KHR != NULL) glad_vkCmdCopyImage2 = (PFN_vkCmdCopyImage2)glad_vkCmdCopyImage2KHR;
    if (glad_vkCmdCopyImage2KHR == NULL && glad_vkCmdCopyImage2 != NULL) glad_vkCmdCopyImage2KHR = (PFN_vkCmdCopyImage2KHR)glad_vkCmdCopyImage2;
    if (glad_vkCmdCopyImageToBuffer2 == NULL && glad_vkCmdCopyImageToBuffer2KHR != NULL) glad_vkCmdCopyImageToBuffer2 = (PFN_vkCmdCopyImageToBuffer2)glad_vkCmdCopyImageToBuffer2KHR;
    if (glad_vkCmdCopyImageToBuffer2KHR == NULL && glad_vkCmdCopyImageToBuffer2 != NULL) glad_vkCmdCopyImageToBuffer2KHR = (PFN_vkCmdCopyImageToBuffer2KHR)glad_vkCmdCopyImageToBuffer2;
    if (glad_vkCmdDispatchBase == NULL && glad_vkCmdDispatchBaseKHR != NULL) glad_vkCmdDispatchBase = (PFN_vkCmdDispatchBase)glad_vkCmdDispatchBaseKHR;
    if (glad_vkCmdDispatchBaseKHR == NULL && glad_vkCmdDispatchBase != NULL) glad_vkCmdDispatchBaseKHR = (PFN_vkCmdDispatchBaseKHR)glad_vkCmdDispatchBase;
    if (glad_vkCmdDrawIndexedIndirectCount == NULL && glad_vkCmdDrawIndexedIndirectCountAMD != NULL) glad_vkCmdDrawIndexedIndirectCount = (PFN_vkCmdDrawIndexedIndirectCount)glad_vkCmdDrawIndexedIndirectCountAMD;
    if (glad_vkCmdDrawIndexedIndirectCount == NULL && glad_vkCmdDrawIndexedIndirectCountKHR != NULL) glad_vkCmdDrawIndexedIndirectCount = (PFN_vkCmdDrawIndexedIndirectCount)glad_vkCmdDrawIndexedIndirectCountKHR;
    if (glad_vkCmdDrawIndexedIndirectCountAMD == NULL && glad_vkCmdDrawIndexedIndirectCount != NULL) glad_vkCmdDrawIndexedIndirectCountAMD = (PFN_vkCmdDrawIndexedIndirectCountAMD)glad_vkCmdDrawIndexedIndirectCount;
    if (glad_vkCmdDrawIndexedIndirectCountAMD == NULL && glad_vkCmdDrawIndexedIndirectCountKHR != NULL) glad_vkCmdDrawIndexedIndirectCountAMD = (PFN_vkCmdDrawIndexedIndirectCountAMD)glad_vkCmdDrawIndexedIndirectCountKHR;
    if (glad_vkCmdDrawIndexedIndirectCountKHR == NULL && glad_vkCmdDrawIndexedIndirectCount != NULL) glad_vkCmdDrawIndexedIndirectCountKHR = (PFN_vkCmdDrawIndexedIndirectCountKHR)glad_vkCmdDrawIndexedIndirectCount;
    if (glad_vkCmdDrawIndexedIndirectCountKHR == NULL && glad_vkCmdDrawIndexedIndirectCountAMD != NULL) glad_vkCmdDrawIndexedIndirectCountKHR = (PFN_vkCmdDrawIndexedIndirectCountKHR)glad_vkCmdDrawIndexedIndirectCountAMD;
    if (glad_vkCmdDrawIndirectCount == NULL && glad_vkCmdDrawIndirectCountAMD != NULL) glad_vkCmdDrawIndirectCount = (PFN_vkCmdDrawIndirectCount)glad_vkCmdDrawIndirectCountAMD;
    if (glad_vkCmdDrawIndirectCount == NULL && glad_vkCmdDrawIndirectCountKHR != NULL) glad_vkCmdDrawIndirectCount = (PFN_vkCmdDrawIndirectCount)glad_vkCmdDrawIndirectCountKHR;
    if (glad_vkCmdDrawIndirectCountAMD == NULL && glad_vkCmdDrawIndirectCount != NULL) glad_vkCmdDrawIndirectCountAMD = (PFN_vkCmdDrawIndirectCountAMD)glad_vkCmdDrawIndirectCount;
    if (glad_vkCmdDrawIndirectCountAMD == NULL && glad_vkCmdDrawIndirectCountKHR != NULL) glad_vkCmdDrawIndirectCountAMD = (PFN_vkCmdDrawIndirectCountAMD)glad_vkCmdDrawIndirectCountKHR;
    if (glad_vkCmdDrawIndirectCountKHR == NULL && glad_vkCmdDrawIndirectCount != NULL) glad_vkCmdDrawIndirectCountKHR = (PFN_vkCmdDrawIndirectCountKHR)glad_vkCmdDrawIndirectCount;
    if (glad_vkCmdDrawIndirectCountKHR == NULL && glad_vkCmdDrawIndirectCountAMD != NULL) glad_vkCmdDrawIndirectCountKHR = (PFN_vkCmdDrawIndirectCountKHR)glad_vkCmdDrawIndirectCountAMD;
    if (glad_vkCmdEndRendering == NULL && glad_vkCmdEndRenderingKHR != NULL) glad_vkCmdEndRendering = (PFN_vkCmdEndRendering)glad_vkCmdEndRenderingKHR;
    if (glad_vkCmdEndRenderingKHR == NULL && glad_vkCmdEndRendering != NULL) glad_vkCmdEndRenderingKHR = (PFN_vkCmdEndRenderingKHR)glad_vkCmdEndRendering;
    if (glad_vkCmdEndRenderPass2 == NULL && glad_vkCmdEndRenderPass2KHR != NULL) glad_vkCmdEndRenderPass2 = (PFN_vkCmdEndRenderPass2)glad_vkCmdEndRenderPass2KHR;
    if (glad_vkCmdEndRenderPass2KHR == NULL && glad_vkCmdEndRenderPass2 != NULL) glad_vkCmdEndRenderPass2KHR = (PFN_vkCmdEndRenderPass2KHR)glad_vkCmdEndRenderPass2;
    if (glad_vkCmdNextSubpass2 == NULL && glad_vkCmdNextSubpass2KHR != NULL) glad_vkCmdNextSubpass2 = (PFN_vkCmdNextSubpass2)glad_vkCmdNextSubpass2KHR;
    if (glad_vkCmdNextSubpass2KHR == NULL && glad_vkCmdNextSubpass2 != NULL) glad_vkCmdNextSubpass2KHR = (PFN_vkCmdNextSubpass2KHR)glad_vkCmdNextSubpass2;
    if (glad_vkCmdPipelineBarrier2 == NULL && glad_vkCmdPipelineBarrier2KHR != NULL) glad_vkCmdPipelineBarrier2 = (PFN_vkCmdPipelineBarrier2)glad_vkCmdPipelineBarrier2KHR;
    if (glad_vkCmdPipelineBarrier2KHR == NULL && glad_vkCmdPipelineBarrier2 != NULL) glad_vkCmdPipelineBarrier2KHR = (PFN_vkCmdPipelineBarrier2KHR)glad_vkCmdPipelineBarrier2;
    if (glad_vkCmdPushConstants2 == NULL && glad_vkCmdPushConstants2KHR != NULL) glad_vkCmdPushConstants2 = (PFN_vkCmdPushConstants2)glad_vkCmdPushConstants2KHR;
    if (glad_vkCmdPushConstants2KHR == NULL && glad_vkCmdPushConstants2 != NULL) glad_vkCmdPushConstants2KHR = (PFN_vkCmdPushConstants2KHR)glad_vkCmdPushConstants2;
    if (glad_vkCmdPushDescriptorSet == NULL && glad_vkCmdPushDescriptorSetKHR != NULL) glad_vkCmdPushDescriptorSet = (PFN_vkCmdPushDescriptorSet)glad_vkCmdPushDescriptorSetKHR;
    if (glad_vkCmdPushDescriptorSet2 == NULL && glad_vkCmdPushDescriptorSet2KHR != NULL) glad_vkCmdPushDescriptorSet2 = (PFN_vkCmdPushDescriptorSet2)glad_vkCmdPushDescriptorSet2KHR;
    if (glad_vkCmdPushDescriptorSet2KHR == NULL && glad_vkCmdPushDescriptorSet2 != NULL) glad_vkCmdPushDescriptorSet2KHR = (PFN_vkCmdPushDescriptorSet2KHR)glad_vkCmdPushDescriptorSet2;
    if (glad_vkCmdPushDescriptorSetKHR == NULL && glad_vkCmdPushDescriptorSet != NULL) glad_vkCmdPushDescriptorSetKHR = (PFN_vkCmdPushDescriptorSetKHR)glad_vkCmdPushDescriptorSet;
    if (glad_vkCmdPushDescriptorSetWithTemplate == NULL && glad_vkCmdPushDescriptorSetWithTemplateKHR != NULL) glad_vkCmdPushDescriptorSetWithTemplate = (PFN_vkCmdPushDescriptorSetWithTemplate)glad_vkCmdPushDescriptorSetWithTemplateKHR;
    if (glad_vkCmdPushDescriptorSetWithTemplate2 == NULL && glad_vkCmdPushDescriptorSetWithTemplate2KHR != NULL) glad_vkCmdPushDescriptorSetWithTemplate2 = (PFN_vkCmdPushDescriptorSetWithTemplate2)glad_vkCmdPushDescriptorSetWithTemplate2KHR;
    if (glad_vkCmdPushDescriptorSetWithTemplate2KHR == NULL && glad_vkCmdPushDescriptorSetWithTemplate2 != NULL) glad_vkCmdPushDescriptorSetWithTemplate2KHR = (PFN_vkCmdPushDescriptorSetWithTemplate2KHR)glad_vkCmdPushDescriptorSetWithTemplate2;
    if (glad_vkCmdPushDescriptorSetWithTemplateKHR == NULL && glad_vkCmdPushDescriptorSetWithTemplate != NULL) glad_vkCmdPushDescriptorSetWithTemplateKHR = (PFN_vkCmdPushDescriptorSetWithTemplateKHR)glad_vkCmdPushDescriptorSetWithTemplate;
    if (glad_vkCmdResetEvent2 == NULL && glad_vkCmdResetEvent2KHR != NULL) glad_vkCmdResetEvent2 = (PFN_vkCmdResetEvent2)glad_vkCmdResetEvent2KHR;
    if (glad_vkCmdResetEvent2KHR == NULL && glad_vkCmdResetEvent2 != NULL) glad_vkCmdResetEvent2KHR = (PFN_vkCmdResetEvent2KHR)glad_vkCmdResetEvent2;
    if (glad_vkCmdResolveImage2 == NULL && glad_vkCmdResolveImage2KHR != NULL) glad_vkCmdResolveImage2 = (PFN_vkCmdResolveImage2)glad_vkCmdResolveImage2KHR;
    if (glad_vkCmdResolveImage2KHR == NULL && glad_vkCmdResolveImage2 != NULL) glad_vkCmdResolveImage2KHR = (PFN_vkCmdResolveImage2KHR)glad_vkCmdResolveImage2;
    if (glad_vkCmdSetCullMode == NULL && glad_vkCmdSetCullModeEXT != NULL) glad_vkCmdSetCullMode = (PFN_vkCmdSetCullMode)glad_vkCmdSetCullModeEXT;
    if (glad_vkCmdSetCullModeEXT == NULL && glad_vkCmdSetCullMode != NULL) glad_vkCmdSetCullModeEXT = (PFN_vkCmdSetCullModeEXT)glad_vkCmdSetCullMode;
    if (glad_vkCmdSetDepthBiasEnable == NULL && glad_vkCmdSetDepthBiasEnableEXT != NULL) glad_vkCmdSetDepthBiasEnable = (PFN_vkCmdSetDepthBiasEnable)glad_vkCmdSetDepthBiasEnableEXT;
    if (glad_vkCmdSetDepthBiasEnableEXT == NULL && glad_vkCmdSetDepthBiasEnable != NULL) glad_vkCmdSetDepthBiasEnableEXT = (PFN_vkCmdSetDepthBiasEnableEXT)glad_vkCmdSetDepthBiasEnable;
    if (glad_vkCmdSetDepthBoundsTestEnable == NULL && glad_vkCmdSetDepthBoundsTestEnableEXT != NULL) glad_vkCmdSetDepthBoundsTestEnable = (PFN_vkCmdSetDepthBoundsTestEnable)glad_vkCmdSetDepthBoundsTestEnableEXT;
    if (glad_vkCmdSetDepthBoundsTestEnableEXT == NULL && glad_vkCmdSetDepthBoundsTestEnable != NULL) glad_vkCmdSetDepthBoundsTestEnableEXT = (PFN_vkCmdSetDepthBoundsTestEnableEXT)glad_vkCmdSetDepthBoundsTestEnable;
    if (glad_vkCmdSetDepthCompareOp == NULL && glad_vkCmdSetDepthCompareOpEXT != NULL) glad_vkCmdSetDepthCompareOp = (PFN_vkCmdSetDepthCompareOp)glad_vkCmdSetDepthCompareOpEXT;
    if (glad_vkCmdSetDepthCompareOpEXT == NULL && glad_vkCmdSetDepthCompareOp != NULL) glad_vkCmdSetDepthCompareOpEXT = (PFN_vkCmdSetDepthCompareOpEXT)glad_vkCmdSetDepthCompareOp;
    if (glad_vkCmdSetDepthTestEnable == NULL && glad_vkCmdSetDepthTestEnableEXT != NULL) glad_vkCmdSetDepthTestEnable = (PFN_vkCmdSetDepthTestEnable)glad_vkCmdSetDepthTestEnableEXT;
    if (glad_vkCmdSetDepthTestEnableEXT == NULL && glad_vkCmdSetDepthTestEnable != NULL) glad_vkCmdSetDepthTestEnableEXT = (PFN_vkCmdSetDepthTestEnableEXT)glad_vkCmdSetDepthTestEnable;
    if (glad_vkCmdSetDepthWriteEnable == NULL && glad_vkCmdSetDepthWriteEnableEXT != NULL) glad_vkCmdSetDepthWriteEnable = (PFN_vkCmdSetDepthWriteEnable)glad_vkCmdSetDepthWriteEnableEXT;
    if (glad_vkCmdSetDepthWriteEnableEXT == NULL && glad_vkCmdSetDepthWriteEnable != NULL) glad_vkCmdSetDepthWriteEnableEXT = (PFN_vkCmdSetDepthWriteEnableEXT)glad_vkCmdSetDepthWriteEnable;
    if (glad_vkCmdSetDeviceMask == NULL && glad_vkCmdSetDeviceMaskKHR != NULL) glad_vkCmdSetDeviceMask = (PFN_vkCmdSetDeviceMask)glad_vkCmdSetDeviceMaskKHR;
    if (glad_vkCmdSetDeviceMaskKHR == NULL && glad_vkCmdSetDeviceMask != NULL) glad_vkCmdSetDeviceMaskKHR = (PFN_vkCmdSetDeviceMaskKHR)glad_vkCmdSetDeviceMask;
    if (glad_vkCmdSetEvent2 == NULL && glad_vkCmdSetEvent2KHR != NULL) glad_vkCmdSetEvent2 = (PFN_vkCmdSetEvent2)glad_vkCmdSetEvent2KHR;
    if (glad_vkCmdSetEvent2KHR == NULL && glad_vkCmdSetEvent2 != NULL) glad_vkCmdSetEvent2KHR = (PFN_vkCmdSetEvent2KHR)glad_vkCmdSetEvent2;
    if (glad_vkCmdSetFrontFace == NULL && glad_vkCmdSetFrontFaceEXT != NULL) glad_vkCmdSetFrontFace = (PFN_vkCmdSetFrontFace)glad_vkCmdSetFrontFaceEXT;
    if (glad_vkCmdSetFrontFaceEXT == NULL && glad_vkCmdSetFrontFace != NULL) glad_vkCmdSetFrontFaceEXT = (PFN_vkCmdSetFrontFaceEXT)glad_vkCmdSetFrontFace;
    if (glad_vkCmdSetLineStipple == NULL && glad_vkCmdSetLineStippleEXT != NULL) glad_vkCmdSetLineStipple = (PFN_vkCmdSetLineStipple)glad_vkCmdSetLineStippleEXT;
    if (glad_vkCmdSetLineStipple == NULL && glad_vkCmdSetLineStippleKHR != NULL) glad_vkCmdSetLineStipple = (PFN_vkCmdSetLineStipple)glad_vkCmdSetLineStippleKHR;
    if (glad_vkCmdSetLineStippleEXT == NULL && glad_vkCmdSetLineStipple != NULL) glad_vkCmdSetLineStippleEXT = (PFN_vkCmdSetLineStippleEXT)glad_vkCmdSetLineStipple;
    if (glad_vkCmdSetLineStippleEXT == NULL && glad_vkCmdSetLineStippleKHR != NULL) glad_vkCmdSetLineStippleEXT = (PFN_vkCmdSetLineStippleEXT)glad_vkCmdSetLineStippleKHR;
    if (glad_vkCmdSetLineStippleKHR == NULL && glad_vkCmdSetLineStipple != NULL) glad_vkCmdSetLineStippleKHR = (PFN_vkCmdSetLineStippleKHR)glad_vkCmdSetLineStipple;
    if (glad_vkCmdSetLineStippleKHR == NULL && glad_vkCmdSetLineStippleEXT != NULL) glad_vkCmdSetLineStippleKHR = (PFN_vkCmdSetLineStippleKHR)glad_vkCmdSetLineStippleEXT;
    if (glad_vkCmdSetPrimitiveRestartEnable == NULL && glad_vkCmdSetPrimitiveRestartEnableEXT != NULL) glad_vkCmdSetPrimitiveRestartEnable = (PFN_vkCmdSetPrimitiveRestartEnable)glad_vkCmdSetPrimitiveRestartEnableEXT;
    if (glad_vkCmdSetPrimitiveRestartEnableEXT == NULL && glad_vkCmdSetPrimitiveRestartEnable != NULL) glad_vkCmdSetPrimitiveRestartEnableEXT = (PFN_vkCmdSetPrimitiveRestartEnableEXT)glad_vkCmdSetPrimitiveRestartEnable;
    if (glad_vkCmdSetPrimitiveTopology == NULL && glad_vkCmdSetPrimitiveTopologyEXT != NULL) glad_vkCmdSetPrimitiveTopology = (PFN_vkCmdSetPrimitiveTopology)glad_vkCmdSetPrimitiveTopologyEXT;
    if (glad_vkCmdSetPrimitiveTopologyEXT == NULL && glad_vkCmdSetPrimitiveTopology != NULL) glad_vkCmdSetPrimitiveTopologyEXT = (PFN_vkCmdSetPrimitiveTopologyEXT)glad_vkCmdSetPrimitiveTopology;
    if (glad_vkCmdSetRasterizerDiscardEnable == NULL && glad_vkCmdSetRasterizerDiscardEnableEXT != NULL) glad_vkCmdSetRasterizerDiscardEnable = (PFN_vkCmdSetRasterizerDiscardEnable)glad_vkCmdSetRasterizerDiscardEnableEXT;
    if (glad_vkCmdSetRasterizerDiscardEnableEXT == NULL && glad_vkCmdSetRasterizerDiscardEnable != NULL) glad_vkCmdSetRasterizerDiscardEnableEXT = (PFN_vkCmdSetRasterizerDiscardEnableEXT)glad_vkCmdSetRasterizerDiscardEnable;
    if (glad_vkCmdSetRenderingAttachmentLocations == NULL && glad_vkCmdSetRenderingAttachmentLocationsKHR != NULL) glad_vkCmdSetRenderingAttachmentLocations = (PFN_vkCmdSetRenderingAttachmentLocations)glad_vkCmdSetRenderingAttachmentLocationsKHR;
    if (glad_vkCmdSetRenderingAttachmentLocationsKHR == NULL && glad_vkCmdSetRenderingAttachmentLocations != NULL) glad_vkCmdSetRenderingAttachmentLocationsKHR = (PFN_vkCmdSetRenderingAttachmentLocationsKHR)glad_vkCmdSetRenderingAttachmentLocations;
    if (glad_vkCmdSetRenderingInputAttachmentIndices == NULL && glad_vkCmdSetRenderingInputAttachmentIndicesKHR != NULL) glad_vkCmdSetRenderingInputAttachmentIndices = (PFN_vkCmdSetRenderingInputAttachmentIndices)glad_vkCmdSetRenderingInputAttachmentIndicesKHR;
    if (glad_vkCmdSetRenderingInputAttachmentIndicesKHR == NULL && glad_vkCmdSetRenderingInputAttachmentIndices != NULL) glad_vkCmdSetRenderingInputAttachmentIndicesKHR = (PFN_vkCmdSetRenderingInputAttachmentIndicesKHR)glad_vkCmdSetRenderingInputAttachmentIndices;
    if (glad_vkCmdSetScissorWithCount == NULL && glad_vkCmdSetScissorWithCountEXT != NULL) glad_vkCmdSetScissorWithCount = (PFN_vkCmdSetScissorWithCount)glad_vkCmdSetScissorWithCountEXT;
    if (glad_vkCmdSetScissorWithCountEXT == NULL && glad_vkCmdSetScissorWithCount != NULL) glad_vkCmdSetScissorWithCountEXT = (PFN_vkCmdSetScissorWithCountEXT)glad_vkCmdSetScissorWithCount;
    if (glad_vkCmdSetStencilOp == NULL && glad_vkCmdSetStencilOpEXT != NULL) glad_vkCmdSetStencilOp = (PFN_vkCmdSetStencilOp)glad_vkCmdSetStencilOpEXT;
    if (glad_vkCmdSetStencilOpEXT == NULL && glad_vkCmdSetStencilOp != NULL) glad_vkCmdSetStencilOpEXT = (PFN_vkCmdSetStencilOpEXT)glad_vkCmdSetStencilOp;
    if (glad_vkCmdSetStencilTestEnable == NULL && glad_vkCmdSetStencilTestEnableEXT != NULL) glad_vkCmdSetStencilTestEnable = (PFN_vkCmdSetStencilTestEnable)glad_vkCmdSetStencilTestEnableEXT;
    if (glad_vkCmdSetStencilTestEnableEXT == NULL && glad_vkCmdSetStencilTestEnable != NULL) glad_vkCmdSetStencilTestEnableEXT = (PFN_vkCmdSetStencilTestEnableEXT)glad_vkCmdSetStencilTestEnable;
    if (glad_vkCmdSetViewportWithCount == NULL && glad_vkCmdSetViewportWithCountEXT != NULL) glad_vkCmdSetViewportWithCount = (PFN_vkCmdSetViewportWithCount)glad_vkCmdSetViewportWithCountEXT;
    if (glad_vkCmdSetViewportWithCountEXT == NULL && glad_vkCmdSetViewportWithCount != NULL) glad_vkCmdSetViewportWithCountEXT = (PFN_vkCmdSetViewportWithCountEXT)glad_vkCmdSetViewportWithCount;
    if (glad_vkCmdWaitEvents2 == NULL && glad_vkCmdWaitEvents2KHR != NULL) glad_vkCmdWaitEvents2 = (PFN_vkCmdWaitEvents2)glad_vkCmdWaitEvents2KHR;
    if (glad_vkCmdWaitEvents2KHR == NULL && glad_vkCmdWaitEvents2 != NULL) glad_vkCmdWaitEvents2KHR = (PFN_vkCmdWaitEvents2KHR)glad_vkCmdWaitEvents2;
    if (glad_vkCmdWriteTimestamp2 == NULL && glad_vkCmdWriteTimestamp2KHR != NULL) glad_vkCmdWriteTimestamp2 = (PFN_vkCmdWriteTimestamp2)glad_vkCmdWriteTimestamp2KHR;
    if (glad_vkCmdWriteTimestamp2KHR == NULL && glad_vkCmdWriteTimestamp2 != NULL) glad_vkCmdWriteTimestamp2KHR = (PFN_vkCmdWriteTimestamp2KHR)glad_vkCmdWriteTimestamp2;
    if (glad_vkCopyImageToImage == NULL && glad_vkCopyImageToImageEXT != NULL) glad_vkCopyImageToImage = (PFN_vkCopyImageToImage)glad_vkCopyImageToImageEXT;
    if (glad_vkCopyImageToImageEXT == NULL && glad_vkCopyImageToImage != NULL) glad_vkCopyImageToImageEXT = (PFN_vkCopyImageToImageEXT)glad_vkCopyImageToImage;
    if (glad_vkCopyImageToMemory == NULL && glad_vkCopyImageToMemoryEXT != NULL) glad_vkCopyImageToMemory = (PFN_vkCopyImageToMemory)glad_vkCopyImageToMemoryEXT;
    if (glad_vkCopyImageToMemoryEXT == NULL && glad_vkCopyImageToMemory != NULL) glad_vkCopyImageToMemoryEXT = (PFN_vkCopyImageToMemoryEXT)glad_vkCopyImageToMemory;
    if (glad_vkCopyMemoryToImage == NULL && glad_vkCopyMemoryToImageEXT != NULL) glad_vkCopyMemoryToImage = (PFN_vkCopyMemoryToImage)glad_vkCopyMemoryToImageEXT;
    if (glad_vkCopyMemoryToImageEXT == NULL && glad_vkCopyMemoryToImage != NULL) glad_vkCopyMemoryToImageEXT = (PFN_vkCopyMemoryToImageEXT)glad_vkCopyMemoryToImage;
    if (glad_vkCreateDescriptorUpdateTemplate == NULL && glad_vkCreateDescriptorUpdateTemplateKHR != NULL) glad_vkCreateDescriptorUpdateTemplate = (PFN_vkCreateDescriptorUpdateTemplate)glad_vkCreateDescriptorUpdateTemplateKHR;
    if (glad_vkCreateDescriptorUpdateTemplateKHR == NULL && glad_vkCreateDescriptorUpdateTemplate != NULL) glad_vkCreateDescriptorUpdateTemplateKHR = (PFN_vkCreateDescriptorUpdateTemplateKHR)glad_vkCreateDescriptorUpdateTemplate;
    if (glad_vkCreatePrivateDataSlot == NULL && glad_vkCreatePrivateDataSlotEXT != NULL) glad_vkCreatePrivateDataSlot = (PFN_vkCreatePrivateDataSlot)glad_vkCreatePrivateDataSlotEXT;
    if (glad_vkCreatePrivateDataSlotEXT == NULL && glad_vkCreatePrivateDataSlot != NULL) glad_vkCreatePrivateDataSlotEXT = (PFN_vkCreatePrivateDataSlotEXT)glad_vkCreatePrivateDataSlot;
    if (glad_vkCreateRenderPass2 == NULL && glad_vkCreateRenderPass2KHR != NULL) glad_vkCreateRenderPass2 = (PFN_vkCreateRenderPass2)glad_vkCreateRenderPass2KHR;
    if (glad_vkCreateRenderPass2KHR == NULL && glad_vkCreateRenderPass2 != NULL) glad_vkCreateRenderPass2KHR = (PFN_vkCreateRenderPass2KHR)glad_vkCreateRenderPass2;
    if (glad_vkCreateSamplerYcbcrConversion == NULL && glad_vkCreateSamplerYcbcrConversionKHR != NULL) glad_vkCreateSamplerYcbcrConversion = (PFN_vkCreateSamplerYcbcrConversion)glad_vkCreateSamplerYcbcrConversionKHR;
    if (glad_vkCreateSamplerYcbcrConversionKHR == NULL && glad_vkCreateSamplerYcbcrConversion != NULL) glad_vkCreateSamplerYcbcrConversionKHR = (PFN_vkCreateSamplerYcbcrConversionKHR)glad_vkCreateSamplerYcbcrConversion;
    if (glad_vkDestroyDescriptorUpdateTemplate == NULL && glad_vkDestroyDescriptorUpdateTemplateKHR != NULL) glad_vkDestroyDescriptorUpdateTemplate = (PFN_vkDestroyDescriptorUpdateTemplate)glad_vkDestroyDescriptorUpdateTemplateKHR;
    if (glad_vkDestroyDescriptorUpdateTemplateKHR == NULL && glad_vkDestroyDescriptorUpdateTemplate != NULL) glad_vkDestroyDescriptorUpdateTemplateKHR = (PFN_vkDestroyDescriptorUpdateTemplateKHR)glad_vkDestroyDescriptorUpdateTemplate;
    if (glad_vkDestroyPrivateDataSlot == NULL && glad_vkDestroyPrivateDataSlotEXT != NULL) glad_vkDestroyPrivateDataSlot = (PFN_vkDestroyPrivateDataSlot)glad_vkDestroyPrivateDataSlotEXT;
    if (glad_vkDestroyPrivateDataSlotEXT == NULL && glad_vkDestroyPrivateDataSlot != NULL) glad_vkDestroyPrivateDataSlotEXT = (PFN_vkDestroyPrivateDataSlotEXT)glad_vkDestroyPrivateDataSlot;
    if (glad_vkDestroySamplerYcbcrConversion == NULL && glad_vkDestroySamplerYcbcrConversionKHR != NULL) glad_vkDestroySamplerYcbcrConversion = (PFN_vkDestroySamplerYcbcrConversion)glad_vkDestroySamplerYcbcrConversionKHR;
    if (glad_vkDestroySamplerYcbcrConversionKHR == NULL && glad_vkDestroySamplerYcbcrConversion != NULL) glad_vkDestroySamplerYcbcrConversionKHR = (PFN_vkDestroySamplerYcbcrConversionKHR)glad_vkDestroySamplerYcbcrConversion;
    if (glad_vkEnumeratePhysicalDeviceGroups == NULL && glad_vkEnumeratePhysicalDeviceGroupsKHR != NULL) glad_vkEnumeratePhysicalDeviceGroups = (PFN_vkEnumeratePhysicalDeviceGroups)glad_vkEnumeratePhysicalDeviceGroupsKHR;
    if (glad_vkEnumeratePhysicalDeviceGroupsKHR == NULL && glad_vkEnumeratePhysicalDeviceGroups != NULL) glad_vkEnumeratePhysicalDeviceGroupsKHR = (PFN_vkEnumeratePhysicalDeviceGroupsKHR)glad_vkEnumeratePhysicalDeviceGroups;
    if (glad_vkGetBufferDeviceAddress == NULL && glad_vkGetBufferDeviceAddressEXT != NULL) glad_vkGetBufferDeviceAddress = (PFN_vkGetBufferDeviceAddress)glad_vkGetBufferDeviceAddressEXT;
    if (glad_vkGetBufferDeviceAddress == NULL && glad_vkGetBufferDeviceAddressKHR != NULL) glad_vkGetBufferDeviceAddress = (PFN_vkGetBufferDeviceAddress)glad_vkGetBufferDeviceAddressKHR;
    if (glad_vkGetBufferDeviceAddressEXT == NULL && glad_vkGetBufferDeviceAddress != NULL) glad_vkGetBufferDeviceAddressEXT = (PFN_vkGetBufferDeviceAddressEXT)glad_vkGetBufferDeviceAddress;
    if (glad_vkGetBufferDeviceAddressEXT == NULL && glad_vkGetBufferDeviceAddressKHR != NULL) glad_vkGetBufferDeviceAddressEXT = (PFN_vkGetBufferDeviceAddressEXT)glad_vkGetBufferDeviceAddressKHR;
    if (glad_vkGetBufferDeviceAddressKHR == NULL && glad_vkGetBufferDeviceAddress != NULL) glad_vkGetBufferDeviceAddressKHR = (PFN_vkGetBufferDeviceAddressKHR)glad_vkGetBufferDeviceAddress;
    if (glad_vkGetBufferDeviceAddressKHR == NULL && glad_vkGetBufferDeviceAddressEXT != NULL) glad_vkGetBufferDeviceAddressKHR = (PFN_vkGetBufferDeviceAddressKHR)glad_vkGetBufferDeviceAddressEXT;
    if (glad_vkGetBufferMemoryRequirements2 == NULL && glad_vkGetBufferMemoryRequirements2KHR != NULL) glad_vkGetBufferMemoryRequirements2 = (PFN_vkGetBufferMemoryRequirements2)glad_vkGetBufferMemoryRequirements2KHR;
    if (glad_vkGetBufferMemoryRequirements2KHR == NULL && glad_vkGetBufferMemoryRequirements2 != NULL) glad_vkGetBufferMemoryRequirements2KHR = (PFN_vkGetBufferMemoryRequirements2KHR)glad_vkGetBufferMemoryRequirements2;
    if (glad_vkGetBufferOpaqueCaptureAddress == NULL && glad_vkGetBufferOpaqueCaptureAddressKHR != NULL) glad_vkGetBufferOpaqueCaptureAddress = (PFN_vkGetBufferOpaqueCaptureAddress)glad_vkGetBufferOpaqueCaptureAddressKHR;
    if (glad_vkGetBufferOpaqueCaptureAddressKHR == NULL && glad_vkGetBufferOpaqueCaptureAddress != NULL) glad_vkGetBufferOpaqueCaptureAddressKHR = (PFN_vkGetBufferOpaqueCaptureAddressKHR)glad_vkGetBufferOpaqueCaptureAddress;
    if (glad_vkGetDescriptorSetLayoutSupport == NULL && glad_vkGetDescriptorSetLayoutSupportKHR != NULL) glad_vkGetDescriptorSetLayoutSupport = (PFN_vkGetDescriptorSetLayoutSupport)glad_vkGetDescriptorSetLayoutSupportKHR;
    if (glad_vkGetDescriptorSetLayoutSupportKHR == NULL && glad_vkGetDescriptorSetLayoutSupport != NULL) glad_vkGetDescriptorSetLayoutSupportKHR = (PFN_vkGetDescriptorSetLayoutSupportKHR)glad_vkGetDescriptorSetLayoutSupport;
    if (glad_vkGetDeviceBufferMemoryRequirements == NULL && glad_vkGetDeviceBufferMemoryRequirementsKHR != NULL) glad_vkGetDeviceBufferMemoryRequirements = (PFN_vkGetDeviceBufferMemoryRequirements)glad_vkGetDeviceBufferMemoryRequirementsKHR;
    if (glad_vkGetDeviceBufferMemoryRequirementsKHR == NULL && glad_vkGetDeviceBufferMemoryRequirements != NULL) glad_vkGetDeviceBufferMemoryRequirementsKHR = (PFN_vkGetDeviceBufferMemoryRequirementsKHR)glad_vkGetDeviceBufferMemoryRequirements;
    if (glad_vkGetDeviceGroupPeerMemoryFeatures == NULL && glad_vkGetDeviceGroupPeerMemoryFeaturesKHR != NULL) glad_vkGetDeviceGroupPeerMemoryFeatures = (PFN_vkGetDeviceGroupPeerMemoryFeatures)glad_vkGetDeviceGroupPeerMemoryFeaturesKHR;
    if (glad_vkGetDeviceGroupPeerMemoryFeaturesKHR == NULL && glad_vkGetDeviceGroupPeerMemoryFeatures != NULL) glad_vkGetDeviceGroupPeerMemoryFeaturesKHR = (PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR)glad_vkGetDeviceGroupPeerMemoryFeatures;
    if (glad_vkGetDeviceImageMemoryRequirements == NULL && glad_vkGetDeviceImageMemoryRequirementsKHR != NULL) glad_vkGetDeviceImageMemoryRequirements = (PFN_vkGetDeviceImageMemoryRequirements)glad_vkGetDeviceImageMemoryRequirementsKHR;
    if (glad_vkGetDeviceImageMemoryRequirementsKHR == NULL && glad_vkGetDeviceImageMemoryRequirements != NULL) glad_vkGetDeviceImageMemoryRequirementsKHR = (PFN_vkGetDeviceImageMemoryRequirementsKHR)glad_vkGetDeviceImageMemoryRequirements;
    if (glad_vkGetDeviceImageSparseMemoryRequirements == NULL && glad_vkGetDeviceImageSparseMemoryRequirementsKHR != NULL) glad_vkGetDeviceImageSparseMemoryRequirements = (PFN_vkGetDeviceImageSparseMemoryRequirements)glad_vkGetDeviceImageSparseMemoryRequirementsKHR;
    if (glad_vkGetDeviceImageSparseMemoryRequirementsKHR == NULL && glad_vkGetDeviceImageSparseMemoryRequirements != NULL) glad_vkGetDeviceImageSparseMemoryRequirementsKHR = (PFN_vkGetDeviceImageSparseMemoryRequirementsKHR)glad_vkGetDeviceImageSparseMemoryRequirements;
    if (glad_vkGetDeviceImageSubresourceLayout == NULL && glad_vkGetDeviceImageSubresourceLayoutKHR != NULL) glad_vkGetDeviceImageSubresourceLayout = (PFN_vkGetDeviceImageSubresourceLayout)glad_vkGetDeviceImageSubresourceLayoutKHR;
    if (glad_vkGetDeviceImageSubresourceLayoutKHR == NULL && glad_vkGetDeviceImageSubresourceLayout != NULL) glad_vkGetDeviceImageSubresourceLayoutKHR = (PFN_vkGetDeviceImageSubresourceLayoutKHR)glad_vkGetDeviceImageSubresourceLayout;
    if (glad_vkGetDeviceMemoryOpaqueCaptureAddress == NULL && glad_vkGetDeviceMemoryOpaqueCaptureAddressKHR != NULL) glad_vkGetDeviceMemoryOpaqueCaptureAddress = (PFN_vkGetDeviceMemoryOpaqueCaptureAddress)glad_vkGetDeviceMemoryOpaqueCaptureAddressKHR;
    if (glad_vkGetDeviceMemoryOpaqueCaptureAddressKHR == NULL && glad_vkGetDeviceMemoryOpaqueCaptureAddress != NULL) glad_vkGetDeviceMemoryOpaqueCaptureAddressKHR = (PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR)glad_vkGetDeviceMemoryOpaqueCaptureAddress;
    if (glad_vkGetImageMemoryRequirements2 == NULL && glad_vkGetImageMemoryRequirements2KHR != NULL) glad_vkGetImageMemoryRequirements2 = (PFN_vkGetImageMemoryRequirements2)glad_vkGetImageMemoryRequirements2KHR;
    if (glad_vkGetImageMemoryRequirements2KHR == NULL && glad_vkGetImageMemoryRequirements2 != NULL) glad_vkGetImageMemoryRequirements2KHR = (PFN_vkGetImageMemoryRequirements2KHR)glad_vkGetImageMemoryRequirements2;
    if (glad_vkGetImageSparseMemoryRequirements2 == NULL && glad_vkGetImageSparseMemoryRequirements2KHR != NULL) glad_vkGetImageSparseMemoryRequirements2 = (PFN_vkGetImageSparseMemoryRequirements2)glad_vkGetImageSparseMemoryRequirements2KHR;
    if (glad_vkGetImageSparseMemoryRequirements2KHR == NULL && glad_vkGetImageSparseMemoryRequirements2 != NULL) glad_vkGetImageSparseMemoryRequirements2KHR = (PFN_vkGetImageSparseMemoryRequirements2KHR)glad_vkGetImageSparseMemoryRequirements2;
    if (glad_vkGetImageSubresourceLayout2 == NULL && glad_vkGetImageSubresourceLayout2EXT != NULL) glad_vkGetImageSubresourceLayout2 = (PFN_vkGetImageSubresourceLayout2)glad_vkGetImageSubresourceLayout2EXT;
    if (glad_vkGetImageSubresourceLayout2 == NULL && glad_vkGetImageSubresourceLayout2KHR != NULL) glad_vkGetImageSubresourceLayout2 = (PFN_vkGetImageSubresourceLayout2)glad_vkGetImageSubresourceLayout2KHR;
    if (glad_vkGetImageSubresourceLayout2EXT == NULL && glad_vkGetImageSubresourceLayout2 != NULL) glad_vkGetImageSubresourceLayout2EXT = (PFN_vkGetImageSubresourceLayout2EXT)glad_vkGetImageSubresourceLayout2;
    if (glad_vkGetImageSubresourceLayout2EXT == NULL && glad_vkGetImageSubresourceLayout2KHR != NULL) glad_vkGetImageSubresourceLayout2EXT = (PFN_vkGetImageSubresourceLayout2EXT)glad_vkGetImageSubresourceLayout2KHR;
    if (glad_vkGetImageSubresourceLayout2KHR == NULL && glad_vkGetImageSubresourceLayout2 != NULL) glad_vkGetImageSubresourceLayout2KHR = (PFN_vkGetImageSubresourceLayout2KHR)glad_vkGetImageSubresourceLayout2;
    if (glad_vkGetImageSubresourceLayout2KHR == NULL && glad_vkGetImageSubresourceLayout2EXT != NULL) glad_vkGetImageSubresourceLayout2KHR = (PFN_vkGetImageSubresourceLayout2KHR)glad_vkGetImageSubresourceLayout2EXT;
    if (glad_vkGetPhysicalDeviceExternalBufferProperties == NULL && glad_vkGetPhysicalDeviceExternalBufferPropertiesKHR != NULL) glad_vkGetPhysicalDeviceExternalBufferProperties = (PFN_vkGetPhysicalDeviceExternalBufferProperties)glad_vkGetPhysicalDeviceExternalBufferPropertiesKHR;
    if (glad_vkGetPhysicalDeviceExternalBufferPropertiesKHR == NULL && glad_vkGetPhysicalDeviceExternalBufferProperties != NULL) glad_vkGetPhysicalDeviceExternalBufferPropertiesKHR = (PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR)glad_vkGetPhysicalDeviceExternalBufferProperties;
    if (glad_vkGetPhysicalDeviceExternalFenceProperties == NULL && glad_vkGetPhysicalDeviceExternalFencePropertiesKHR != NULL) glad_vkGetPhysicalDeviceExternalFenceProperties = (PFN_vkGetPhysicalDeviceExternalFenceProperties)glad_vkGetPhysicalDeviceExternalFencePropertiesKHR;
    if (glad_vkGetPhysicalDeviceExternalFencePropertiesKHR == NULL && glad_vkGetPhysicalDeviceExternalFenceProperties != NULL) glad_vkGetPhysicalDeviceExternalFencePropertiesKHR = (PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR)glad_vkGetPhysicalDeviceExternalFenceProperties;
    if (glad_vkGetPhysicalDeviceExternalSemaphoreProperties == NULL && glad_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR != NULL) glad_vkGetPhysicalDeviceExternalSemaphoreProperties = (PFN_vkGetPhysicalDeviceExternalSemaphoreProperties)glad_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR;
    if (glad_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR == NULL && glad_vkGetPhysicalDeviceExternalSemaphoreProperties != NULL) glad_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = (PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR)glad_vkGetPhysicalDeviceExternalSemaphoreProperties;
    if (glad_vkGetPhysicalDeviceFeatures2 == NULL && glad_vkGetPhysicalDeviceFeatures2KHR != NULL) glad_vkGetPhysicalDeviceFeatures2 = (PFN_vkGetPhysicalDeviceFeatures2)glad_vkGetPhysicalDeviceFeatures2KHR;
    if (glad_vkGetPhysicalDeviceFeatures2KHR == NULL && glad_vkGetPhysicalDeviceFeatures2 != NULL) glad_vkGetPhysicalDeviceFeatures2KHR = (PFN_vkGetPhysicalDeviceFeatures2KHR)glad_vkGetPhysicalDeviceFeatures2;
    if (glad_vkGetPhysicalDeviceFormatProperties2 == NULL && glad_vkGetPhysicalDeviceFormatProperties2KHR != NULL) glad_vkGetPhysicalDeviceFormatProperties2 = (PFN_vkGetPhysicalDeviceFormatProperties2)glad_vkGetPhysicalDeviceFormatProperties2KHR;
    if (glad_vkGetPhysicalDeviceFormatProperties2KHR == NULL && glad_vkGetPhysicalDeviceFormatProperties2 != NULL) glad_vkGetPhysicalDeviceFormatProperties2KHR = (PFN_vkGetPhysicalDeviceFormatProperties2KHR)glad_vkGetPhysicalDeviceFormatProperties2;
    if (glad_vkGetPhysicalDeviceImageFormatProperties2 == NULL && glad_vkGetPhysicalDeviceImageFormatProperties2KHR != NULL) glad_vkGetPhysicalDeviceImageFormatProperties2 = (PFN_vkGetPhysicalDeviceImageFormatProperties2)glad_vkGetPhysicalDeviceImageFormatProperties2KHR;
    if (glad_vkGetPhysicalDeviceImageFormatProperties2KHR == NULL && glad_vkGetPhysicalDeviceImageFormatProperties2 != NULL) glad_vkGetPhysicalDeviceImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceImageFormatProperties2KHR)glad_vkGetPhysicalDeviceImageFormatProperties2;
    if (glad_vkGetPhysicalDeviceMemoryProperties2 == NULL && glad_vkGetPhysicalDeviceMemoryProperties2KHR != NULL) glad_vkGetPhysicalDeviceMemoryProperties2 = (PFN_vkGetPhysicalDeviceMemoryProperties2)glad_vkGetPhysicalDeviceMemoryProperties2KHR;
    if (glad_vkGetPhysicalDeviceMemoryProperties2KHR == NULL && glad_vkGetPhysicalDeviceMemoryProperties2 != NULL) glad_vkGetPhysicalDeviceMemoryProperties2KHR = (PFN_vkGetPhysicalDeviceMemoryProperties2KHR)glad_vkGetPhysicalDeviceMemoryProperties2;
    if (glad_vkGetPhysicalDeviceProperties2 == NULL && glad_vkGetPhysicalDeviceProperties2KHR != NULL) glad_vkGetPhysicalDeviceProperties2 = (PFN_vkGetPhysicalDeviceProperties2)glad_vkGetPhysicalDeviceProperties2KHR;
    if (glad_vkGetPhysicalDeviceProperties2KHR == NULL && glad_vkGetPhysicalDeviceProperties2 != NULL) glad_vkGetPhysicalDeviceProperties2KHR = (PFN_vkGetPhysicalDeviceProperties2KHR)glad_vkGetPhysicalDeviceProperties2;
    if (glad_vkGetPhysicalDeviceQueueFamilyProperties2 == NULL && glad_vkGetPhysicalDeviceQueueFamilyProperties2KHR != NULL) glad_vkGetPhysicalDeviceQueueFamilyProperties2 = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2)glad_vkGetPhysicalDeviceQueueFamilyProperties2KHR;
    if (glad_vkGetPhysicalDeviceQueueFamilyProperties2KHR == NULL && glad_vkGetPhysicalDeviceQueueFamilyProperties2 != NULL) glad_vkGetPhysicalDeviceQueueFamilyProperties2KHR = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR)glad_vkGetPhysicalDeviceQueueFamilyProperties2;
    if (glad_vkGetPhysicalDeviceSparseImageFormatProperties2 == NULL && glad_vkGetPhysicalDeviceSparseImageFormatProperties2KHR != NULL) glad_vkGetPhysicalDeviceSparseImageFormatProperties2 = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2)glad_vkGetPhysicalDeviceSparseImageFormatProperties2KHR;
    if (glad_vkGetPhysicalDeviceSparseImageFormatProperties2KHR == NULL && glad_vkGetPhysicalDeviceSparseImageFormatProperties2 != NULL) glad_vkGetPhysicalDeviceSparseImageFormatProperties2KHR = (PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR)glad_vkGetPhysicalDeviceSparseImageFormatProperties2;
    if (glad_vkGetPhysicalDeviceToolProperties == NULL && glad_vkGetPhysicalDeviceToolPropertiesEXT != NULL) glad_vkGetPhysicalDeviceToolProperties = (PFN_vkGetPhysicalDeviceToolProperties)glad_vkGetPhysicalDeviceToolPropertiesEXT;
    if (glad_vkGetPhysicalDeviceToolPropertiesEXT == NULL && glad_vkGetPhysicalDeviceToolProperties != NULL) glad_vkGetPhysicalDeviceToolPropertiesEXT = (PFN_vkGetPhysicalDeviceToolPropertiesEXT)glad_vkGetPhysicalDeviceToolProperties;
    if (glad_vkGetPrivateData == NULL && glad_vkGetPrivateDataEXT != NULL) glad_vkGetPrivateData = (PFN_vkGetPrivateData)glad_vkGetPrivateDataEXT;
    if (glad_vkGetPrivateDataEXT == NULL && glad_vkGetPrivateData != NULL) glad_vkGetPrivateDataEXT = (PFN_vkGetPrivateDataEXT)glad_vkGetPrivateData;
    if (glad_vkGetRenderingAreaGranularity == NULL && glad_vkGetRenderingAreaGranularityKHR != NULL) glad_vkGetRenderingAreaGranularity = (PFN_vkGetRenderingAreaGranularity)glad_vkGetRenderingAreaGranularityKHR;
    if (glad_vkGetRenderingAreaGranularityKHR == NULL && glad_vkGetRenderingAreaGranularity != NULL) glad_vkGetRenderingAreaGranularityKHR = (PFN_vkGetRenderingAreaGranularityKHR)glad_vkGetRenderingAreaGranularity;
    if (glad_vkGetSemaphoreCounterValue == NULL && glad_vkGetSemaphoreCounterValueKHR != NULL) glad_vkGetSemaphoreCounterValue = (PFN_vkGetSemaphoreCounterValue)glad_vkGetSemaphoreCounterValueKHR;
    if (glad_vkGetSemaphoreCounterValueKHR == NULL && glad_vkGetSemaphoreCounterValue != NULL) glad_vkGetSemaphoreCounterValueKHR = (PFN_vkGetSemaphoreCounterValueKHR)glad_vkGetSemaphoreCounterValue;
    if (glad_vkMapMemory2 == NULL && glad_vkMapMemory2KHR != NULL) glad_vkMapMemory2 = (PFN_vkMapMemory2)glad_vkMapMemory2KHR;
    if (glad_vkMapMemory2KHR == NULL && glad_vkMapMemory2 != NULL) glad_vkMapMemory2KHR = (PFN_vkMapMemory2KHR)glad_vkMapMemory2;
    if (glad_vkQueueSubmit2 == NULL && glad_vkQueueSubmit2KHR != NULL) glad_vkQueueSubmit2 = (PFN_vkQueueSubmit2)glad_vkQueueSubmit2KHR;
    if (glad_vkQueueSubmit2KHR == NULL && glad_vkQueueSubmit2 != NULL) glad_vkQueueSubmit2KHR = (PFN_vkQueueSubmit2KHR)glad_vkQueueSubmit2;
    if (glad_vkResetQueryPool == NULL && glad_vkResetQueryPoolEXT != NULL) glad_vkResetQueryPool = (PFN_vkResetQueryPool)glad_vkResetQueryPoolEXT;
    if (glad_vkResetQueryPoolEXT == NULL && glad_vkResetQueryPool != NULL) glad_vkResetQueryPoolEXT = (PFN_vkResetQueryPoolEXT)glad_vkResetQueryPool;
    if (glad_vkSetPrivateData == NULL && glad_vkSetPrivateDataEXT != NULL) glad_vkSetPrivateData = (PFN_vkSetPrivateData)glad_vkSetPrivateDataEXT;
    if (glad_vkSetPrivateDataEXT == NULL && glad_vkSetPrivateData != NULL) glad_vkSetPrivateDataEXT = (PFN_vkSetPrivateDataEXT)glad_vkSetPrivateData;
    if (glad_vkSignalSemaphore == NULL && glad_vkSignalSemaphoreKHR != NULL) glad_vkSignalSemaphore = (PFN_vkSignalSemaphore)glad_vkSignalSemaphoreKHR;
    if (glad_vkSignalSemaphoreKHR == NULL && glad_vkSignalSemaphore != NULL) glad_vkSignalSemaphoreKHR = (PFN_vkSignalSemaphoreKHR)glad_vkSignalSemaphore;
    if (glad_vkTransitionImageLayout == NULL && glad_vkTransitionImageLayoutEXT != NULL) glad_vkTransitionImageLayout = (PFN_vkTransitionImageLayout)glad_vkTransitionImageLayoutEXT;
    if (glad_vkTransitionImageLayoutEXT == NULL && glad_vkTransitionImageLayout != NULL) glad_vkTransitionImageLayoutEXT = (PFN_vkTransitionImageLayoutEXT)glad_vkTransitionImageLayout;
    if (glad_vkTrimCommandPool == NULL && glad_vkTrimCommandPoolKHR != NULL) glad_vkTrimCommandPool = (PFN_vkTrimCommandPool)glad_vkTrimCommandPoolKHR;
    if (glad_vkTrimCommandPoolKHR == NULL && glad_vkTrimCommandPool != NULL) glad_vkTrimCommandPoolKHR = (PFN_vkTrimCommandPoolKHR)glad_vkTrimCommandPool;
    if (glad_vkUnmapMemory2 == NULL && glad_vkUnmapMemory2KHR != NULL) glad_vkUnmapMemory2 = (PFN_vkUnmapMemory2)glad_vkUnmapMemory2KHR;
    if (glad_vkUnmapMemory2KHR == NULL && glad_vkUnmapMemory2 != NULL) glad_vkUnmapMemory2KHR = (PFN_vkUnmapMemory2KHR)glad_vkUnmapMemory2;
    if (glad_vkUpdateDescriptorSetWithTemplate == NULL && glad_vkUpdateDescriptorSetWithTemplateKHR != NULL) glad_vkUpdateDescriptorSetWithTemplate = (PFN_vkUpdateDescriptorSetWithTemplate)glad_vkUpdateDescriptorSetWithTemplateKHR;
    if (glad_vkUpdateDescriptorSetWithTemplateKHR == NULL && glad_vkUpdateDescriptorSetWithTemplate != NULL) glad_vkUpdateDescriptorSetWithTemplateKHR = (PFN_vkUpdateDescriptorSetWithTemplateKHR)glad_vkUpdateDescriptorSetWithTemplate;
    if (glad_vkWaitSemaphores == NULL && glad_vkWaitSemaphoresKHR != NULL) glad_vkWaitSemaphores = (PFN_vkWaitSemaphores)glad_vkWaitSemaphoresKHR;
    if (glad_vkWaitSemaphoresKHR == NULL && glad_vkWaitSemaphores != NULL) glad_vkWaitSemaphoresKHR = (PFN_vkWaitSemaphoresKHR)glad_vkWaitSemaphores;
}

static int glad_vk_get_extensions( VkPhysicalDevice physical_device, uint32_t *out_extension_count, char ***out_extensions) {
    uint32_t i;
    uint32_t instance_extension_count = 0;
    uint32_t device_extension_count = 0;
    uint32_t max_extension_count = 0;
    uint32_t total_extension_count = 0;
    char **extensions = NULL;
    VkExtensionProperties *ext_properties = NULL;
    VkResult result;

    if (glad_vkEnumerateInstanceExtensionProperties == NULL || (physical_device != NULL && glad_vkEnumerateDeviceExtensionProperties == NULL)) {
        return 0;
    }

    result = glad_vkEnumerateInstanceExtensionProperties(NULL, &instance_extension_count, NULL);
    if (result != VK_SUCCESS) {
        return 0;
    }

    if (physical_device != NULL) {
        result = glad_vkEnumerateDeviceExtensionProperties(physical_device, NULL, &device_extension_count, NULL);
        if (result != VK_SUCCESS) {
            return 0;
        }
    }

    total_extension_count = instance_extension_count + device_extension_count;
    if (total_extension_count <= 0) {
        return 0;
    }

    max_extension_count = instance_extension_count > device_extension_count
        ? instance_extension_count : device_extension_count;

    ext_properties = (VkExtensionProperties*) malloc(max_extension_count * sizeof(VkExtensionProperties));
    if (ext_properties == NULL) {
        goto glad_vk_get_extensions_error;
    }

    result = glad_vkEnumerateInstanceExtensionProperties(NULL, &instance_extension_count, ext_properties);
    if (result != VK_SUCCESS) {
        goto glad_vk_get_extensions_error;
    }

    extensions = (char**) calloc(total_extension_count, sizeof(char*));
    if (extensions == NULL) {
        goto glad_vk_get_extensions_error;
    }

    for (i = 0; i < instance_extension_count; ++i) {
        VkExtensionProperties ext = ext_properties[i];

        size_t extension_name_length = strlen(ext.extensionName) + 1;
        extensions[i] = (char*) malloc(extension_name_length * sizeof(char));
        if (extensions[i] == NULL) {
            goto glad_vk_get_extensions_error;
        }
        memcpy(extensions[i], ext.extensionName, extension_name_length * sizeof(char));
    }

    if (physical_device != NULL) {
        result = glad_vkEnumerateDeviceExtensionProperties(physical_device, NULL, &device_extension_count, ext_properties);
        if (result != VK_SUCCESS) {
            goto glad_vk_get_extensions_error;
        }

        for (i = 0; i < device_extension_count; ++i) {
            VkExtensionProperties ext = ext_properties[i];

            size_t extension_name_length = strlen(ext.extensionName) + 1;
            extensions[instance_extension_count + i] = (char*) malloc(extension_name_length * sizeof(char));
            if (extensions[instance_extension_count + i] == NULL) {
                goto glad_vk_get_extensions_error;
            }
            memcpy(extensions[instance_extension_count + i], ext.extensionName, extension_name_length * sizeof(char));
        }
    }

    free((void*) ext_properties);

    *out_extension_count = total_extension_count;
    *out_extensions = extensions;

    return 1;

glad_vk_get_extensions_error:
    free((void*) ext_properties);
    if (extensions != NULL) {
        for (i = 0; i < total_extension_count; ++i) {
            free((void*) extensions[i]);
        }
        free(extensions);
    }
    return 0;
}

static void glad_vk_free_extensions(uint32_t extension_count, char **extensions) {
    uint32_t i;

    for(i = 0; i < extension_count ; ++i) {
        free((void*) (extensions[i]));
    }

    free((void*) extensions);
}

static int glad_vk_has_extension(const char *name, uint32_t extension_count, char **extensions) {
    uint32_t i;

    for (i = 0; i < extension_count; ++i) {
        if(extensions[i] != NULL && strcmp(name, extensions[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

static GLADapiproc glad_vk_get_proc_from_userptr(void *userptr, const char* name) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
}

static int glad_vk_find_extensions_vulkan( VkPhysicalDevice physical_device) {
    uint32_t extension_count = 0;
    char **extensions = NULL;
    if (!glad_vk_get_extensions(physical_device, &extension_count, &extensions)) return 0;

    GLAD_VK_AMD_draw_indirect_count = glad_vk_has_extension("VK_AMD_draw_indirect_count", extension_count, extensions);
    GLAD_VK_EXT_buffer_device_address = glad_vk_has_extension("VK_EXT_buffer_device_address", extension_count, extensions);
    GLAD_VK_EXT_extended_dynamic_state = glad_vk_has_extension("VK_EXT_extended_dynamic_state", extension_count, extensions);
    GLAD_VK_EXT_extended_dynamic_state2 = glad_vk_has_extension("VK_EXT_extended_dynamic_state2", extension_count, extensions);
    GLAD_VK_EXT_host_image_copy = glad_vk_has_extension("VK_EXT_host_image_copy", extension_count, extensions);
    GLAD_VK_EXT_host_query_reset = glad_vk_has_extension("VK_EXT_host_query_reset", extension_count, extensions);
    GLAD_VK_EXT_image_compression_control = glad_vk_has_extension("VK_EXT_image_compression_control", extension_count, extensions);
    GLAD_VK_EXT_line_rasterization = glad_vk_has_extension("VK_EXT_line_rasterization", extension_count, extensions);
    GLAD_VK_EXT_private_data = glad_vk_has_extension("VK_EXT_private_data", extension_count, extensions);
    GLAD_VK_EXT_shader_object = glad_vk_has_extension("VK_EXT_shader_object", extension_count, extensions);
    GLAD_VK_EXT_tooling_info = glad_vk_has_extension("VK_EXT_tooling_info", extension_count, extensions);
    GLAD_VK_KHR_bind_memory2 = glad_vk_has_extension("VK_KHR_bind_memory2", extension_count, extensions);
    GLAD_VK_KHR_buffer_device_address = glad_vk_has_extension("VK_KHR_buffer_device_address", extension_count, extensions);
    GLAD_VK_KHR_copy_commands2 = glad_vk_has_extension("VK_KHR_copy_commands2", extension_count, extensions);
    GLAD_VK_KHR_create_renderpass2 = glad_vk_has_extension("VK_KHR_create_renderpass2", extension_count, extensions);
    GLAD_VK_KHR_descriptor_update_template = glad_vk_has_extension("VK_KHR_descriptor_update_template", extension_count, extensions);
    GLAD_VK_KHR_device_group = glad_vk_has_extension("VK_KHR_device_group", extension_count, extensions);
    GLAD_VK_KHR_device_group_creation = glad_vk_has_extension("VK_KHR_device_group_creation", extension_count, extensions);
    GLAD_VK_KHR_draw_indirect_count = glad_vk_has_extension("VK_KHR_draw_indirect_count", extension_count, extensions);
    GLAD_VK_KHR_dynamic_rendering = glad_vk_has_extension("VK_KHR_dynamic_rendering", extension_count, extensions);
    GLAD_VK_KHR_dynamic_rendering_local_read = glad_vk_has_extension("VK_KHR_dynamic_rendering_local_read", extension_count, extensions);
    GLAD_VK_KHR_external_fence_capabilities = glad_vk_has_extension("VK_KHR_external_fence_capabilities", extension_count, extensions);
    GLAD_VK_KHR_external_memory_capabilities = glad_vk_has_extension("VK_KHR_external_memory_capabilities", extension_count, extensions);
    GLAD_VK_KHR_external_semaphore_capabilities = glad_vk_has_extension("VK_KHR_external_semaphore_capabilities", extension_count, extensions);
    GLAD_VK_KHR_get_memory_requirements2 = glad_vk_has_extension("VK_KHR_get_memory_requirements2", extension_count, extensions);
    GLAD_VK_KHR_get_physical_device_properties2 = glad_vk_has_extension("VK_KHR_get_physical_device_properties2", extension_count, extensions);
    GLAD_VK_KHR_line_rasterization = glad_vk_has_extension("VK_KHR_line_rasterization", extension_count, extensions);
    GLAD_VK_KHR_maintenance1 = glad_vk_has_extension("VK_KHR_maintenance1", extension_count, extensions);
    GLAD_VK_KHR_maintenance3 = glad_vk_has_extension("VK_KHR_maintenance3", extension_count, extensions);
    GLAD_VK_KHR_maintenance4 = glad_vk_has_extension("VK_KHR_maintenance4", extension_count, extensions);
    GLAD_VK_KHR_maintenance5 = glad_vk_has_extension("VK_KHR_maintenance5", extension_count, extensions);
    GLAD_VK_KHR_maintenance6 = glad_vk_has_extension("VK_KHR_maintenance6", extension_count, extensions);
    GLAD_VK_KHR_map_memory2 = glad_vk_has_extension("VK_KHR_map_memory2", extension_count, extensions);
    GLAD_VK_KHR_push_descriptor = glad_vk_has_extension("VK_KHR_push_descriptor", extension_count, extensions);
    GLAD_VK_KHR_sampler_ycbcr_conversion = glad_vk_has_extension("VK_KHR_sampler_ycbcr_conversion", extension_count, extensions);
    GLAD_VK_KHR_synchronization2 = glad_vk_has_extension("VK_KHR_synchronization2", extension_count, extensions);
    GLAD_VK_KHR_timeline_semaphore = glad_vk_has_extension("VK_KHR_timeline_semaphore", extension_count, extensions);

    GLAD_UNUSED(&glad_vk_has_extension);

    glad_vk_free_extensions(extension_count, extensions);

    return 1;
}

static int glad_vk_find_core_vulkan( VkPhysicalDevice physical_device) {
    int major = 1;
    int minor = 0;

#ifdef VK_VERSION_1_1
    if (glad_vkEnumerateInstanceVersion != NULL) {
        uint32_t version;
        VkResult result;

        result = glad_vkEnumerateInstanceVersion(&version);
        if (result == VK_SUCCESS) {
            major = (int) VK_VERSION_MAJOR(version);
            minor = (int) VK_VERSION_MINOR(version);
        }
    }
#endif

    if (physical_device != NULL && glad_vkGetPhysicalDeviceProperties != NULL) {
        VkPhysicalDeviceProperties properties;
        glad_vkGetPhysicalDeviceProperties(physical_device, &properties);

        major = (int) VK_VERSION_MAJOR(properties.apiVersion);
        minor = (int) VK_VERSION_MINOR(properties.apiVersion);
    }

    GLAD_VK_VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
    GLAD_VK_VERSION_1_1 = (major == 1 && minor >= 1) || major > 1;
    GLAD_VK_VERSION_1_2 = (major == 1 && minor >= 2) || major > 1;
    GLAD_VK_VERSION_1_3 = (major == 1 && minor >= 3) || major > 1;
    GLAD_VK_VERSION_1_4 = (major == 1 && minor >= 4) || major > 1;

    return GLAD_MAKE_VERSION(major, minor);
}

int gladLoadVulkanUserPtr( VkPhysicalDevice physical_device, GLADuserptrloadfunc load, void *userptr) {
    int version;

#ifdef VK_VERSION_1_1
    glad_vkEnumerateInstanceVersion  = (PFN_vkEnumerateInstanceVersion) load(userptr, "vkEnumerateInstanceVersion");
#endif
    version = glad_vk_find_core_vulkan( physical_device);
    if (!version) {
        return 0;
    }

    glad_vk_load_VK_VERSION_1_0(load, userptr);
    glad_vk_load_VK_VERSION_1_1(load, userptr);
    glad_vk_load_VK_VERSION_1_2(load, userptr);
    glad_vk_load_VK_VERSION_1_3(load, userptr);
    glad_vk_load_VK_VERSION_1_4(load, userptr);

    if (!glad_vk_find_extensions_vulkan( physical_device)) return 0;
    glad_vk_load_VK_AMD_draw_indirect_count(load, userptr);
    glad_vk_load_VK_EXT_buffer_device_address(load, userptr);
    glad_vk_load_VK_EXT_extended_dynamic_state(load, userptr);
    glad_vk_load_VK_EXT_extended_dynamic_state2(load, userptr);
    glad_vk_load_VK_EXT_host_image_copy(load, userptr);
    glad_vk_load_VK_EXT_host_query_reset(load, userptr);
    glad_vk_load_VK_EXT_image_compression_control(load, userptr);
    glad_vk_load_VK_EXT_line_rasterization(load, userptr);
    glad_vk_load_VK_EXT_private_data(load, userptr);
    glad_vk_load_VK_EXT_shader_object(load, userptr);
    glad_vk_load_VK_EXT_tooling_info(load, userptr);
    glad_vk_load_VK_KHR_bind_memory2(load, userptr);
    glad_vk_load_VK_KHR_buffer_device_address(load, userptr);
    glad_vk_load_VK_KHR_copy_commands2(load, userptr);
    glad_vk_load_VK_KHR_create_renderpass2(load, userptr);
    glad_vk_load_VK_KHR_descriptor_update_template(load, userptr);
    glad_vk_load_VK_KHR_device_group(load, userptr);
    glad_vk_load_VK_KHR_device_group_creation(load, userptr);
    glad_vk_load_VK_KHR_draw_indirect_count(load, userptr);
    glad_vk_load_VK_KHR_dynamic_rendering(load, userptr);
    glad_vk_load_VK_KHR_dynamic_rendering_local_read(load, userptr);
    glad_vk_load_VK_KHR_external_fence_capabilities(load, userptr);
    glad_vk_load_VK_KHR_external_memory_capabilities(load, userptr);
    glad_vk_load_VK_KHR_external_semaphore_capabilities(load, userptr);
    glad_vk_load_VK_KHR_get_memory_requirements2(load, userptr);
    glad_vk_load_VK_KHR_get_physical_device_properties2(load, userptr);
    glad_vk_load_VK_KHR_line_rasterization(load, userptr);
    glad_vk_load_VK_KHR_maintenance1(load, userptr);
    glad_vk_load_VK_KHR_maintenance3(load, userptr);
    glad_vk_load_VK_KHR_maintenance4(load, userptr);
    glad_vk_load_VK_KHR_maintenance5(load, userptr);
    glad_vk_load_VK_KHR_maintenance6(load, userptr);
    glad_vk_load_VK_KHR_map_memory2(load, userptr);
    glad_vk_load_VK_KHR_push_descriptor(load, userptr);
    glad_vk_load_VK_KHR_sampler_ycbcr_conversion(load, userptr);
    glad_vk_load_VK_KHR_synchronization2(load, userptr);
    glad_vk_load_VK_KHR_timeline_semaphore(load, userptr);

    glad_vk_resolve_aliases();

    return version;
}


int gladLoadVulkan( VkPhysicalDevice physical_device, GLADloadfunc load) {
    return gladLoadVulkanUserPtr( physical_device, glad_vk_get_proc_from_userptr, GLAD_GNUC_EXTENSION (void*) load);
}



 
void gladInstallVulkanDebug(void) {
    glad_debug_vkAcquireNextImage2KHR = glad_debug_impl_vkAcquireNextImage2KHR;
    glad_debug_vkAllocateCommandBuffers = glad_debug_impl_vkAllocateCommandBuffers;
    glad_debug_vkAllocateDescriptorSets = glad_debug_impl_vkAllocateDescriptorSets;
    glad_debug_vkAllocateMemory = glad_debug_impl_vkAllocateMemory;
    glad_debug_vkBeginCommandBuffer = glad_debug_impl_vkBeginCommandBuffer;
    glad_debug_vkBindBufferMemory = glad_debug_impl_vkBindBufferMemory;
    glad_debug_vkBindBufferMemory2 = glad_debug_impl_vkBindBufferMemory2;
    glad_debug_vkBindBufferMemory2KHR = glad_debug_impl_vkBindBufferMemory2KHR;
    glad_debug_vkBindImageMemory = glad_debug_impl_vkBindImageMemory;
    glad_debug_vkBindImageMemory2 = glad_debug_impl_vkBindImageMemory2;
    glad_debug_vkBindImageMemory2KHR = glad_debug_impl_vkBindImageMemory2KHR;
    glad_debug_vkCmdBeginQuery = glad_debug_impl_vkCmdBeginQuery;
    glad_debug_vkCmdBeginRenderPass = glad_debug_impl_vkCmdBeginRenderPass;
    glad_debug_vkCmdBeginRenderPass2 = glad_debug_impl_vkCmdBeginRenderPass2;
    glad_debug_vkCmdBeginRenderPass2KHR = glad_debug_impl_vkCmdBeginRenderPass2KHR;
    glad_debug_vkCmdBeginRendering = glad_debug_impl_vkCmdBeginRendering;
    glad_debug_vkCmdBeginRenderingKHR = glad_debug_impl_vkCmdBeginRenderingKHR;
    glad_debug_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT = glad_debug_impl_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT;
    glad_debug_vkCmdBindDescriptorSets = glad_debug_impl_vkCmdBindDescriptorSets;
    glad_debug_vkCmdBindDescriptorSets2 = glad_debug_impl_vkCmdBindDescriptorSets2;
    glad_debug_vkCmdBindDescriptorSets2KHR = glad_debug_impl_vkCmdBindDescriptorSets2KHR;
    glad_debug_vkCmdBindIndexBuffer = glad_debug_impl_vkCmdBindIndexBuffer;
    glad_debug_vkCmdBindIndexBuffer2 = glad_debug_impl_vkCmdBindIndexBuffer2;
    glad_debug_vkCmdBindIndexBuffer2KHR = glad_debug_impl_vkCmdBindIndexBuffer2KHR;
    glad_debug_vkCmdBindPipeline = glad_debug_impl_vkCmdBindPipeline;
    glad_debug_vkCmdBindShadersEXT = glad_debug_impl_vkCmdBindShadersEXT;
    glad_debug_vkCmdBindVertexBuffers = glad_debug_impl_vkCmdBindVertexBuffers;
    glad_debug_vkCmdBindVertexBuffers2 = glad_debug_impl_vkCmdBindVertexBuffers2;
    glad_debug_vkCmdBindVertexBuffers2EXT = glad_debug_impl_vkCmdBindVertexBuffers2EXT;
    glad_debug_vkCmdBlitImage = glad_debug_impl_vkCmdBlitImage;
    glad_debug_vkCmdBlitImage2 = glad_debug_impl_vkCmdBlitImage2;
    glad_debug_vkCmdBlitImage2KHR = glad_debug_impl_vkCmdBlitImage2KHR;
    glad_debug_vkCmdClearAttachments = glad_debug_impl_vkCmdClearAttachments;
    glad_debug_vkCmdClearColorImage = glad_debug_impl_vkCmdClearColorImage;
    glad_debug_vkCmdClearDepthStencilImage = glad_debug_impl_vkCmdClearDepthStencilImage;
    glad_debug_vkCmdCopyBuffer = glad_debug_impl_vkCmdCopyBuffer;
    glad_debug_vkCmdCopyBuffer2 = glad_debug_impl_vkCmdCopyBuffer2;
    glad_debug_vkCmdCopyBuffer2KHR = glad_debug_impl_vkCmdCopyBuffer2KHR;
    glad_debug_vkCmdCopyBufferToImage = glad_debug_impl_vkCmdCopyBufferToImage;
    glad_debug_vkCmdCopyBufferToImage2 = glad_debug_impl_vkCmdCopyBufferToImage2;
    glad_debug_vkCmdCopyBufferToImage2KHR = glad_debug_impl_vkCmdCopyBufferToImage2KHR;
    glad_debug_vkCmdCopyImage = glad_debug_impl_vkCmdCopyImage;
    glad_debug_vkCmdCopyImage2 = glad_debug_impl_vkCmdCopyImage2;
    glad_debug_vkCmdCopyImage2KHR = glad_debug_impl_vkCmdCopyImage2KHR;
    glad_debug_vkCmdCopyImageToBuffer = glad_debug_impl_vkCmdCopyImageToBuffer;
    glad_debug_vkCmdCopyImageToBuffer2 = glad_debug_impl_vkCmdCopyImageToBuffer2;
    glad_debug_vkCmdCopyImageToBuffer2KHR = glad_debug_impl_vkCmdCopyImageToBuffer2KHR;
    glad_debug_vkCmdCopyQueryPoolResults = glad_debug_impl_vkCmdCopyQueryPoolResults;
    glad_debug_vkCmdDispatch = glad_debug_impl_vkCmdDispatch;
    glad_debug_vkCmdDispatchBase = glad_debug_impl_vkCmdDispatchBase;
    glad_debug_vkCmdDispatchBaseKHR = glad_debug_impl_vkCmdDispatchBaseKHR;
    glad_debug_vkCmdDispatchIndirect = glad_debug_impl_vkCmdDispatchIndirect;
    glad_debug_vkCmdDraw = glad_debug_impl_vkCmdDraw;
    glad_debug_vkCmdDrawIndexed = glad_debug_impl_vkCmdDrawIndexed;
    glad_debug_vkCmdDrawIndexedIndirect = glad_debug_impl_vkCmdDrawIndexedIndirect;
    glad_debug_vkCmdDrawIndexedIndirectCount = glad_debug_impl_vkCmdDrawIndexedIndirectCount;
    glad_debug_vkCmdDrawIndexedIndirectCountAMD = glad_debug_impl_vkCmdDrawIndexedIndirectCountAMD;
    glad_debug_vkCmdDrawIndexedIndirectCountKHR = glad_debug_impl_vkCmdDrawIndexedIndirectCountKHR;
    glad_debug_vkCmdDrawIndirect = glad_debug_impl_vkCmdDrawIndirect;
    glad_debug_vkCmdDrawIndirectCount = glad_debug_impl_vkCmdDrawIndirectCount;
    glad_debug_vkCmdDrawIndirectCountAMD = glad_debug_impl_vkCmdDrawIndirectCountAMD;
    glad_debug_vkCmdDrawIndirectCountKHR = glad_debug_impl_vkCmdDrawIndirectCountKHR;
    glad_debug_vkCmdEndQuery = glad_debug_impl_vkCmdEndQuery;
    glad_debug_vkCmdEndRenderPass = glad_debug_impl_vkCmdEndRenderPass;
    glad_debug_vkCmdEndRenderPass2 = glad_debug_impl_vkCmdEndRenderPass2;
    glad_debug_vkCmdEndRenderPass2KHR = glad_debug_impl_vkCmdEndRenderPass2KHR;
    glad_debug_vkCmdEndRendering = glad_debug_impl_vkCmdEndRendering;
    glad_debug_vkCmdEndRenderingKHR = glad_debug_impl_vkCmdEndRenderingKHR;
    glad_debug_vkCmdExecuteCommands = glad_debug_impl_vkCmdExecuteCommands;
    glad_debug_vkCmdFillBuffer = glad_debug_impl_vkCmdFillBuffer;
    glad_debug_vkCmdNextSubpass = glad_debug_impl_vkCmdNextSubpass;
    glad_debug_vkCmdNextSubpass2 = glad_debug_impl_vkCmdNextSubpass2;
    glad_debug_vkCmdNextSubpass2KHR = glad_debug_impl_vkCmdNextSubpass2KHR;
    glad_debug_vkCmdPipelineBarrier = glad_debug_impl_vkCmdPipelineBarrier;
    glad_debug_vkCmdPipelineBarrier2 = glad_debug_impl_vkCmdPipelineBarrier2;
    glad_debug_vkCmdPipelineBarrier2KHR = glad_debug_impl_vkCmdPipelineBarrier2KHR;
    glad_debug_vkCmdPushConstants = glad_debug_impl_vkCmdPushConstants;
    glad_debug_vkCmdPushConstants2 = glad_debug_impl_vkCmdPushConstants2;
    glad_debug_vkCmdPushConstants2KHR = glad_debug_impl_vkCmdPushConstants2KHR;
    glad_debug_vkCmdPushDescriptorSet = glad_debug_impl_vkCmdPushDescriptorSet;
    glad_debug_vkCmdPushDescriptorSet2 = glad_debug_impl_vkCmdPushDescriptorSet2;
    glad_debug_vkCmdPushDescriptorSet2KHR = glad_debug_impl_vkCmdPushDescriptorSet2KHR;
    glad_debug_vkCmdPushDescriptorSetKHR = glad_debug_impl_vkCmdPushDescriptorSetKHR;
    glad_debug_vkCmdPushDescriptorSetWithTemplate = glad_debug_impl_vkCmdPushDescriptorSetWithTemplate;
    glad_debug_vkCmdPushDescriptorSetWithTemplate2 = glad_debug_impl_vkCmdPushDescriptorSetWithTemplate2;
    glad_debug_vkCmdPushDescriptorSetWithTemplate2KHR = glad_debug_impl_vkCmdPushDescriptorSetWithTemplate2KHR;
    glad_debug_vkCmdPushDescriptorSetWithTemplateKHR = glad_debug_impl_vkCmdPushDescriptorSetWithTemplateKHR;
    glad_debug_vkCmdResetEvent = glad_debug_impl_vkCmdResetEvent;
    glad_debug_vkCmdResetEvent2 = glad_debug_impl_vkCmdResetEvent2;
    glad_debug_vkCmdResetEvent2KHR = glad_debug_impl_vkCmdResetEvent2KHR;
    glad_debug_vkCmdResetQueryPool = glad_debug_impl_vkCmdResetQueryPool;
    glad_debug_vkCmdResolveImage = glad_debug_impl_vkCmdResolveImage;
    glad_debug_vkCmdResolveImage2 = glad_debug_impl_vkCmdResolveImage2;
    glad_debug_vkCmdResolveImage2KHR = glad_debug_impl_vkCmdResolveImage2KHR;
    glad_debug_vkCmdSetAlphaToCoverageEnableEXT = glad_debug_impl_vkCmdSetAlphaToCoverageEnableEXT;
    glad_debug_vkCmdSetAlphaToOneEnableEXT = glad_debug_impl_vkCmdSetAlphaToOneEnableEXT;
    glad_debug_vkCmdSetBlendConstants = glad_debug_impl_vkCmdSetBlendConstants;
    glad_debug_vkCmdSetColorBlendAdvancedEXT = glad_debug_impl_vkCmdSetColorBlendAdvancedEXT;
    glad_debug_vkCmdSetColorBlendEnableEXT = glad_debug_impl_vkCmdSetColorBlendEnableEXT;
    glad_debug_vkCmdSetColorBlendEquationEXT = glad_debug_impl_vkCmdSetColorBlendEquationEXT;
    glad_debug_vkCmdSetColorWriteMaskEXT = glad_debug_impl_vkCmdSetColorWriteMaskEXT;
    glad_debug_vkCmdSetConservativeRasterizationModeEXT = glad_debug_impl_vkCmdSetConservativeRasterizationModeEXT;
    glad_debug_vkCmdSetCoverageModulationModeNV = glad_debug_impl_vkCmdSetCoverageModulationModeNV;
    glad_debug_vkCmdSetCoverageModulationTableEnableNV = glad_debug_impl_vkCmdSetCoverageModulationTableEnableNV;
    glad_debug_vkCmdSetCoverageModulationTableNV = glad_debug_impl_vkCmdSetCoverageModulationTableNV;
    glad_debug_vkCmdSetCoverageReductionModeNV = glad_debug_impl_vkCmdSetCoverageReductionModeNV;
    glad_debug_vkCmdSetCoverageToColorEnableNV = glad_debug_impl_vkCmdSetCoverageToColorEnableNV;
    glad_debug_vkCmdSetCoverageToColorLocationNV = glad_debug_impl_vkCmdSetCoverageToColorLocationNV;
    glad_debug_vkCmdSetCullMode = glad_debug_impl_vkCmdSetCullMode;
    glad_debug_vkCmdSetCullModeEXT = glad_debug_impl_vkCmdSetCullModeEXT;
    glad_debug_vkCmdSetDepthBias = glad_debug_impl_vkCmdSetDepthBias;
    glad_debug_vkCmdSetDepthBiasEnable = glad_debug_impl_vkCmdSetDepthBiasEnable;
    glad_debug_vkCmdSetDepthBiasEnableEXT = glad_debug_impl_vkCmdSetDepthBiasEnableEXT;
    glad_debug_vkCmdSetDepthBounds = glad_debug_impl_vkCmdSetDepthBounds;
    glad_debug_vkCmdSetDepthBoundsTestEnable = glad_debug_impl_vkCmdSetDepthBoundsTestEnable;
    glad_debug_vkCmdSetDepthBoundsTestEnableEXT = glad_debug_impl_vkCmdSetDepthBoundsTestEnableEXT;
    glad_debug_vkCmdSetDepthClampEnableEXT = glad_debug_impl_vkCmdSetDepthClampEnableEXT;
    glad_debug_vkCmdSetDepthClampRangeEXT = glad_debug_impl_vkCmdSetDepthClampRangeEXT;
    glad_debug_vkCmdSetDepthClipEnableEXT = glad_debug_impl_vkCmdSetDepthClipEnableEXT;
    glad_debug_vkCmdSetDepthClipNegativeOneToOneEXT = glad_debug_impl_vkCmdSetDepthClipNegativeOneToOneEXT;
    glad_debug_vkCmdSetDepthCompareOp = glad_debug_impl_vkCmdSetDepthCompareOp;
    glad_debug_vkCmdSetDepthCompareOpEXT = glad_debug_impl_vkCmdSetDepthCompareOpEXT;
    glad_debug_vkCmdSetDepthTestEnable = glad_debug_impl_vkCmdSetDepthTestEnable;
    glad_debug_vkCmdSetDepthTestEnableEXT = glad_debug_impl_vkCmdSetDepthTestEnableEXT;
    glad_debug_vkCmdSetDepthWriteEnable = glad_debug_impl_vkCmdSetDepthWriteEnable;
    glad_debug_vkCmdSetDepthWriteEnableEXT = glad_debug_impl_vkCmdSetDepthWriteEnableEXT;
    glad_debug_vkCmdSetDescriptorBufferOffsets2EXT = glad_debug_impl_vkCmdSetDescriptorBufferOffsets2EXT;
    glad_debug_vkCmdSetDeviceMask = glad_debug_impl_vkCmdSetDeviceMask;
    glad_debug_vkCmdSetDeviceMaskKHR = glad_debug_impl_vkCmdSetDeviceMaskKHR;
    glad_debug_vkCmdSetEvent = glad_debug_impl_vkCmdSetEvent;
    glad_debug_vkCmdSetEvent2 = glad_debug_impl_vkCmdSetEvent2;
    glad_debug_vkCmdSetEvent2KHR = glad_debug_impl_vkCmdSetEvent2KHR;
    glad_debug_vkCmdSetExtraPrimitiveOverestimationSizeEXT = glad_debug_impl_vkCmdSetExtraPrimitiveOverestimationSizeEXT;
    glad_debug_vkCmdSetFrontFace = glad_debug_impl_vkCmdSetFrontFace;
    glad_debug_vkCmdSetFrontFaceEXT = glad_debug_impl_vkCmdSetFrontFaceEXT;
    glad_debug_vkCmdSetLineRasterizationModeEXT = glad_debug_impl_vkCmdSetLineRasterizationModeEXT;
    glad_debug_vkCmdSetLineStipple = glad_debug_impl_vkCmdSetLineStipple;
    glad_debug_vkCmdSetLineStippleEXT = glad_debug_impl_vkCmdSetLineStippleEXT;
    glad_debug_vkCmdSetLineStippleEnableEXT = glad_debug_impl_vkCmdSetLineStippleEnableEXT;
    glad_debug_vkCmdSetLineStippleKHR = glad_debug_impl_vkCmdSetLineStippleKHR;
    glad_debug_vkCmdSetLineWidth = glad_debug_impl_vkCmdSetLineWidth;
    glad_debug_vkCmdSetLogicOpEXT = glad_debug_impl_vkCmdSetLogicOpEXT;
    glad_debug_vkCmdSetLogicOpEnableEXT = glad_debug_impl_vkCmdSetLogicOpEnableEXT;
    glad_debug_vkCmdSetPatchControlPointsEXT = glad_debug_impl_vkCmdSetPatchControlPointsEXT;
    glad_debug_vkCmdSetPolygonModeEXT = glad_debug_impl_vkCmdSetPolygonModeEXT;
    glad_debug_vkCmdSetPrimitiveRestartEnable = glad_debug_impl_vkCmdSetPrimitiveRestartEnable;
    glad_debug_vkCmdSetPrimitiveRestartEnableEXT = glad_debug_impl_vkCmdSetPrimitiveRestartEnableEXT;
    glad_debug_vkCmdSetPrimitiveTopology = glad_debug_impl_vkCmdSetPrimitiveTopology;
    glad_debug_vkCmdSetPrimitiveTopologyEXT = glad_debug_impl_vkCmdSetPrimitiveTopologyEXT;
    glad_debug_vkCmdSetProvokingVertexModeEXT = glad_debug_impl_vkCmdSetProvokingVertexModeEXT;
    glad_debug_vkCmdSetRasterizationSamplesEXT = glad_debug_impl_vkCmdSetRasterizationSamplesEXT;
    glad_debug_vkCmdSetRasterizationStreamEXT = glad_debug_impl_vkCmdSetRasterizationStreamEXT;
    glad_debug_vkCmdSetRasterizerDiscardEnable = glad_debug_impl_vkCmdSetRasterizerDiscardEnable;
    glad_debug_vkCmdSetRasterizerDiscardEnableEXT = glad_debug_impl_vkCmdSetRasterizerDiscardEnableEXT;
    glad_debug_vkCmdSetRenderingAttachmentLocations = glad_debug_impl_vkCmdSetRenderingAttachmentLocations;
    glad_debug_vkCmdSetRenderingAttachmentLocationsKHR = glad_debug_impl_vkCmdSetRenderingAttachmentLocationsKHR;
    glad_debug_vkCmdSetRenderingInputAttachmentIndices = glad_debug_impl_vkCmdSetRenderingInputAttachmentIndices;
    glad_debug_vkCmdSetRenderingInputAttachmentIndicesKHR = glad_debug_impl_vkCmdSetRenderingInputAttachmentIndicesKHR;
    glad_debug_vkCmdSetRepresentativeFragmentTestEnableNV = glad_debug_impl_vkCmdSetRepresentativeFragmentTestEnableNV;
    glad_debug_vkCmdSetSampleLocationsEnableEXT = glad_debug_impl_vkCmdSetSampleLocationsEnableEXT;
    glad_debug_vkCmdSetSampleMaskEXT = glad_debug_impl_vkCmdSetSampleMaskEXT;
    glad_debug_vkCmdSetScissor = glad_debug_impl_vkCmdSetScissor;
    glad_debug_vkCmdSetScissorWithCount = glad_debug_impl_vkCmdSetScissorWithCount;
    glad_debug_vkCmdSetScissorWithCountEXT = glad_debug_impl_vkCmdSetScissorWithCountEXT;
    glad_debug_vkCmdSetShadingRateImageEnableNV = glad_debug_impl_vkCmdSetShadingRateImageEnableNV;
    glad_debug_vkCmdSetStencilCompareMask = glad_debug_impl_vkCmdSetStencilCompareMask;
    glad_debug_vkCmdSetStencilOp = glad_debug_impl_vkCmdSetStencilOp;
    glad_debug_vkCmdSetStencilOpEXT = glad_debug_impl_vkCmdSetStencilOpEXT;
    glad_debug_vkCmdSetStencilReference = glad_debug_impl_vkCmdSetStencilReference;
    glad_debug_vkCmdSetStencilTestEnable = glad_debug_impl_vkCmdSetStencilTestEnable;
    glad_debug_vkCmdSetStencilTestEnableEXT = glad_debug_impl_vkCmdSetStencilTestEnableEXT;
    glad_debug_vkCmdSetStencilWriteMask = glad_debug_impl_vkCmdSetStencilWriteMask;
    glad_debug_vkCmdSetTessellationDomainOriginEXT = glad_debug_impl_vkCmdSetTessellationDomainOriginEXT;
    glad_debug_vkCmdSetVertexInputEXT = glad_debug_impl_vkCmdSetVertexInputEXT;
    glad_debug_vkCmdSetViewport = glad_debug_impl_vkCmdSetViewport;
    glad_debug_vkCmdSetViewportSwizzleNV = glad_debug_impl_vkCmdSetViewportSwizzleNV;
    glad_debug_vkCmdSetViewportWScalingEnableNV = glad_debug_impl_vkCmdSetViewportWScalingEnableNV;
    glad_debug_vkCmdSetViewportWithCount = glad_debug_impl_vkCmdSetViewportWithCount;
    glad_debug_vkCmdSetViewportWithCountEXT = glad_debug_impl_vkCmdSetViewportWithCountEXT;
    glad_debug_vkCmdUpdateBuffer = glad_debug_impl_vkCmdUpdateBuffer;
    glad_debug_vkCmdWaitEvents = glad_debug_impl_vkCmdWaitEvents;
    glad_debug_vkCmdWaitEvents2 = glad_debug_impl_vkCmdWaitEvents2;
    glad_debug_vkCmdWaitEvents2KHR = glad_debug_impl_vkCmdWaitEvents2KHR;
    glad_debug_vkCmdWriteTimestamp = glad_debug_impl_vkCmdWriteTimestamp;
    glad_debug_vkCmdWriteTimestamp2 = glad_debug_impl_vkCmdWriteTimestamp2;
    glad_debug_vkCmdWriteTimestamp2KHR = glad_debug_impl_vkCmdWriteTimestamp2KHR;
    glad_debug_vkCopyImageToImage = glad_debug_impl_vkCopyImageToImage;
    glad_debug_vkCopyImageToImageEXT = glad_debug_impl_vkCopyImageToImageEXT;
    glad_debug_vkCopyImageToMemory = glad_debug_impl_vkCopyImageToMemory;
    glad_debug_vkCopyImageToMemoryEXT = glad_debug_impl_vkCopyImageToMemoryEXT;
    glad_debug_vkCopyMemoryToImage = glad_debug_impl_vkCopyMemoryToImage;
    glad_debug_vkCopyMemoryToImageEXT = glad_debug_impl_vkCopyMemoryToImageEXT;
    glad_debug_vkCreateBuffer = glad_debug_impl_vkCreateBuffer;
    glad_debug_vkCreateBufferView = glad_debug_impl_vkCreateBufferView;
    glad_debug_vkCreateCommandPool = glad_debug_impl_vkCreateCommandPool;
    glad_debug_vkCreateComputePipelines = glad_debug_impl_vkCreateComputePipelines;
    glad_debug_vkCreateDescriptorPool = glad_debug_impl_vkCreateDescriptorPool;
    glad_debug_vkCreateDescriptorSetLayout = glad_debug_impl_vkCreateDescriptorSetLayout;
    glad_debug_vkCreateDescriptorUpdateTemplate = glad_debug_impl_vkCreateDescriptorUpdateTemplate;
    glad_debug_vkCreateDescriptorUpdateTemplateKHR = glad_debug_impl_vkCreateDescriptorUpdateTemplateKHR;
    glad_debug_vkCreateDevice = glad_debug_impl_vkCreateDevice;
    glad_debug_vkCreateEvent = glad_debug_impl_vkCreateEvent;
    glad_debug_vkCreateFence = glad_debug_impl_vkCreateFence;
    glad_debug_vkCreateFramebuffer = glad_debug_impl_vkCreateFramebuffer;
    glad_debug_vkCreateGraphicsPipelines = glad_debug_impl_vkCreateGraphicsPipelines;
    glad_debug_vkCreateImage = glad_debug_impl_vkCreateImage;
    glad_debug_vkCreateImageView = glad_debug_impl_vkCreateImageView;
    glad_debug_vkCreateInstance = glad_debug_impl_vkCreateInstance;
    glad_debug_vkCreatePipelineCache = glad_debug_impl_vkCreatePipelineCache;
    glad_debug_vkCreatePipelineLayout = glad_debug_impl_vkCreatePipelineLayout;
    glad_debug_vkCreatePrivateDataSlot = glad_debug_impl_vkCreatePrivateDataSlot;
    glad_debug_vkCreatePrivateDataSlotEXT = glad_debug_impl_vkCreatePrivateDataSlotEXT;
    glad_debug_vkCreateQueryPool = glad_debug_impl_vkCreateQueryPool;
    glad_debug_vkCreateRenderPass = glad_debug_impl_vkCreateRenderPass;
    glad_debug_vkCreateRenderPass2 = glad_debug_impl_vkCreateRenderPass2;
    glad_debug_vkCreateRenderPass2KHR = glad_debug_impl_vkCreateRenderPass2KHR;
    glad_debug_vkCreateSampler = glad_debug_impl_vkCreateSampler;
    glad_debug_vkCreateSamplerYcbcrConversion = glad_debug_impl_vkCreateSamplerYcbcrConversion;
    glad_debug_vkCreateSamplerYcbcrConversionKHR = glad_debug_impl_vkCreateSamplerYcbcrConversionKHR;
    glad_debug_vkCreateSemaphore = glad_debug_impl_vkCreateSemaphore;
    glad_debug_vkCreateShaderModule = glad_debug_impl_vkCreateShaderModule;
    glad_debug_vkCreateShadersEXT = glad_debug_impl_vkCreateShadersEXT;
    glad_debug_vkDestroyBuffer = glad_debug_impl_vkDestroyBuffer;
    glad_debug_vkDestroyBufferView = glad_debug_impl_vkDestroyBufferView;
    glad_debug_vkDestroyCommandPool = glad_debug_impl_vkDestroyCommandPool;
    glad_debug_vkDestroyDescriptorPool = glad_debug_impl_vkDestroyDescriptorPool;
    glad_debug_vkDestroyDescriptorSetLayout = glad_debug_impl_vkDestroyDescriptorSetLayout;
    glad_debug_vkDestroyDescriptorUpdateTemplate = glad_debug_impl_vkDestroyDescriptorUpdateTemplate;
    glad_debug_vkDestroyDescriptorUpdateTemplateKHR = glad_debug_impl_vkDestroyDescriptorUpdateTemplateKHR;
    glad_debug_vkDestroyDevice = glad_debug_impl_vkDestroyDevice;
    glad_debug_vkDestroyEvent = glad_debug_impl_vkDestroyEvent;
    glad_debug_vkDestroyFence = glad_debug_impl_vkDestroyFence;
    glad_debug_vkDestroyFramebuffer = glad_debug_impl_vkDestroyFramebuffer;
    glad_debug_vkDestroyImage = glad_debug_impl_vkDestroyImage;
    glad_debug_vkDestroyImageView = glad_debug_impl_vkDestroyImageView;
    glad_debug_vkDestroyInstance = glad_debug_impl_vkDestroyInstance;
    glad_debug_vkDestroyPipeline = glad_debug_impl_vkDestroyPipeline;
    glad_debug_vkDestroyPipelineCache = glad_debug_impl_vkDestroyPipelineCache;
    glad_debug_vkDestroyPipelineLayout = glad_debug_impl_vkDestroyPipelineLayout;
    glad_debug_vkDestroyPrivateDataSlot = glad_debug_impl_vkDestroyPrivateDataSlot;
    glad_debug_vkDestroyPrivateDataSlotEXT = glad_debug_impl_vkDestroyPrivateDataSlotEXT;
    glad_debug_vkDestroyQueryPool = glad_debug_impl_vkDestroyQueryPool;
    glad_debug_vkDestroyRenderPass = glad_debug_impl_vkDestroyRenderPass;
    glad_debug_vkDestroySampler = glad_debug_impl_vkDestroySampler;
    glad_debug_vkDestroySamplerYcbcrConversion = glad_debug_impl_vkDestroySamplerYcbcrConversion;
    glad_debug_vkDestroySamplerYcbcrConversionKHR = glad_debug_impl_vkDestroySamplerYcbcrConversionKHR;
    glad_debug_vkDestroySemaphore = glad_debug_impl_vkDestroySemaphore;
    glad_debug_vkDestroyShaderEXT = glad_debug_impl_vkDestroyShaderEXT;
    glad_debug_vkDestroyShaderModule = glad_debug_impl_vkDestroyShaderModule;
    glad_debug_vkDeviceWaitIdle = glad_debug_impl_vkDeviceWaitIdle;
    glad_debug_vkEndCommandBuffer = glad_debug_impl_vkEndCommandBuffer;
    glad_debug_vkEnumerateDeviceExtensionProperties = glad_debug_impl_vkEnumerateDeviceExtensionProperties;
    glad_debug_vkEnumerateDeviceLayerProperties = glad_debug_impl_vkEnumerateDeviceLayerProperties;
    glad_debug_vkEnumerateInstanceExtensionProperties = glad_debug_impl_vkEnumerateInstanceExtensionProperties;
    glad_debug_vkEnumerateInstanceLayerProperties = glad_debug_impl_vkEnumerateInstanceLayerProperties;
    glad_debug_vkEnumerateInstanceVersion = glad_debug_impl_vkEnumerateInstanceVersion;
    glad_debug_vkEnumeratePhysicalDeviceGroups = glad_debug_impl_vkEnumeratePhysicalDeviceGroups;
    glad_debug_vkEnumeratePhysicalDeviceGroupsKHR = glad_debug_impl_vkEnumeratePhysicalDeviceGroupsKHR;
    glad_debug_vkEnumeratePhysicalDevices = glad_debug_impl_vkEnumeratePhysicalDevices;
    glad_debug_vkFlushMappedMemoryRanges = glad_debug_impl_vkFlushMappedMemoryRanges;
    glad_debug_vkFreeCommandBuffers = glad_debug_impl_vkFreeCommandBuffers;
    glad_debug_vkFreeDescriptorSets = glad_debug_impl_vkFreeDescriptorSets;
    glad_debug_vkFreeMemory = glad_debug_impl_vkFreeMemory;
    glad_debug_vkGetBufferDeviceAddress = glad_debug_impl_vkGetBufferDeviceAddress;
    glad_debug_vkGetBufferDeviceAddressEXT = glad_debug_impl_vkGetBufferDeviceAddressEXT;
    glad_debug_vkGetBufferDeviceAddressKHR = glad_debug_impl_vkGetBufferDeviceAddressKHR;
    glad_debug_vkGetBufferMemoryRequirements = glad_debug_impl_vkGetBufferMemoryRequirements;
    glad_debug_vkGetBufferMemoryRequirements2 = glad_debug_impl_vkGetBufferMemoryRequirements2;
    glad_debug_vkGetBufferMemoryRequirements2KHR = glad_debug_impl_vkGetBufferMemoryRequirements2KHR;
    glad_debug_vkGetBufferOpaqueCaptureAddress = glad_debug_impl_vkGetBufferOpaqueCaptureAddress;
    glad_debug_vkGetBufferOpaqueCaptureAddressKHR = glad_debug_impl_vkGetBufferOpaqueCaptureAddressKHR;
    glad_debug_vkGetDescriptorSetLayoutSupport = glad_debug_impl_vkGetDescriptorSetLayoutSupport;
    glad_debug_vkGetDescriptorSetLayoutSupportKHR = glad_debug_impl_vkGetDescriptorSetLayoutSupportKHR;
    glad_debug_vkGetDeviceBufferMemoryRequirements = glad_debug_impl_vkGetDeviceBufferMemoryRequirements;
    glad_debug_vkGetDeviceBufferMemoryRequirementsKHR = glad_debug_impl_vkGetDeviceBufferMemoryRequirementsKHR;
    glad_debug_vkGetDeviceGroupPeerMemoryFeatures = glad_debug_impl_vkGetDeviceGroupPeerMemoryFeatures;
    glad_debug_vkGetDeviceGroupPeerMemoryFeaturesKHR = glad_debug_impl_vkGetDeviceGroupPeerMemoryFeaturesKHR;
    glad_debug_vkGetDeviceGroupPresentCapabilitiesKHR = glad_debug_impl_vkGetDeviceGroupPresentCapabilitiesKHR;
    glad_debug_vkGetDeviceGroupSurfacePresentModesKHR = glad_debug_impl_vkGetDeviceGroupSurfacePresentModesKHR;
    glad_debug_vkGetDeviceImageMemoryRequirements = glad_debug_impl_vkGetDeviceImageMemoryRequirements;
    glad_debug_vkGetDeviceImageMemoryRequirementsKHR = glad_debug_impl_vkGetDeviceImageMemoryRequirementsKHR;
    glad_debug_vkGetDeviceImageSparseMemoryRequirements = glad_debug_impl_vkGetDeviceImageSparseMemoryRequirements;
    glad_debug_vkGetDeviceImageSparseMemoryRequirementsKHR = glad_debug_impl_vkGetDeviceImageSparseMemoryRequirementsKHR;
    glad_debug_vkGetDeviceImageSubresourceLayout = glad_debug_impl_vkGetDeviceImageSubresourceLayout;
    glad_debug_vkGetDeviceImageSubresourceLayoutKHR = glad_debug_impl_vkGetDeviceImageSubresourceLayoutKHR;
    glad_debug_vkGetDeviceMemoryCommitment = glad_debug_impl_vkGetDeviceMemoryCommitment;
    glad_debug_vkGetDeviceMemoryOpaqueCaptureAddress = glad_debug_impl_vkGetDeviceMemoryOpaqueCaptureAddress;
    glad_debug_vkGetDeviceMemoryOpaqueCaptureAddressKHR = glad_debug_impl_vkGetDeviceMemoryOpaqueCaptureAddressKHR;
    glad_debug_vkGetDeviceProcAddr = glad_debug_impl_vkGetDeviceProcAddr;
    glad_debug_vkGetDeviceQueue = glad_debug_impl_vkGetDeviceQueue;
    glad_debug_vkGetDeviceQueue2 = glad_debug_impl_vkGetDeviceQueue2;
    glad_debug_vkGetEventStatus = glad_debug_impl_vkGetEventStatus;
    glad_debug_vkGetFenceStatus = glad_debug_impl_vkGetFenceStatus;
    glad_debug_vkGetImageMemoryRequirements = glad_debug_impl_vkGetImageMemoryRequirements;
    glad_debug_vkGetImageMemoryRequirements2 = glad_debug_impl_vkGetImageMemoryRequirements2;
    glad_debug_vkGetImageMemoryRequirements2KHR = glad_debug_impl_vkGetImageMemoryRequirements2KHR;
    glad_debug_vkGetImageSparseMemoryRequirements = glad_debug_impl_vkGetImageSparseMemoryRequirements;
    glad_debug_vkGetImageSparseMemoryRequirements2 = glad_debug_impl_vkGetImageSparseMemoryRequirements2;
    glad_debug_vkGetImageSparseMemoryRequirements2KHR = glad_debug_impl_vkGetImageSparseMemoryRequirements2KHR;
    glad_debug_vkGetImageSubresourceLayout = glad_debug_impl_vkGetImageSubresourceLayout;
    glad_debug_vkGetImageSubresourceLayout2 = glad_debug_impl_vkGetImageSubresourceLayout2;
    glad_debug_vkGetImageSubresourceLayout2EXT = glad_debug_impl_vkGetImageSubresourceLayout2EXT;
    glad_debug_vkGetImageSubresourceLayout2KHR = glad_debug_impl_vkGetImageSubresourceLayout2KHR;
    glad_debug_vkGetInstanceProcAddr = glad_debug_impl_vkGetInstanceProcAddr;
    glad_debug_vkGetPhysicalDeviceExternalBufferProperties = glad_debug_impl_vkGetPhysicalDeviceExternalBufferProperties;
    glad_debug_vkGetPhysicalDeviceExternalBufferPropertiesKHR = glad_debug_impl_vkGetPhysicalDeviceExternalBufferPropertiesKHR;
    glad_debug_vkGetPhysicalDeviceExternalFenceProperties = glad_debug_impl_vkGetPhysicalDeviceExternalFenceProperties;
    glad_debug_vkGetPhysicalDeviceExternalFencePropertiesKHR = glad_debug_impl_vkGetPhysicalDeviceExternalFencePropertiesKHR;
    glad_debug_vkGetPhysicalDeviceExternalSemaphoreProperties = glad_debug_impl_vkGetPhysicalDeviceExternalSemaphoreProperties;
    glad_debug_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = glad_debug_impl_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR;
    glad_debug_vkGetPhysicalDeviceFeatures = glad_debug_impl_vkGetPhysicalDeviceFeatures;
    glad_debug_vkGetPhysicalDeviceFeatures2 = glad_debug_impl_vkGetPhysicalDeviceFeatures2;
    glad_debug_vkGetPhysicalDeviceFeatures2KHR = glad_debug_impl_vkGetPhysicalDeviceFeatures2KHR;
    glad_debug_vkGetPhysicalDeviceFormatProperties = glad_debug_impl_vkGetPhysicalDeviceFormatProperties;
    glad_debug_vkGetPhysicalDeviceFormatProperties2 = glad_debug_impl_vkGetPhysicalDeviceFormatProperties2;
    glad_debug_vkGetPhysicalDeviceFormatProperties2KHR = glad_debug_impl_vkGetPhysicalDeviceFormatProperties2KHR;
    glad_debug_vkGetPhysicalDeviceImageFormatProperties = glad_debug_impl_vkGetPhysicalDeviceImageFormatProperties;
    glad_debug_vkGetPhysicalDeviceImageFormatProperties2 = glad_debug_impl_vkGetPhysicalDeviceImageFormatProperties2;
    glad_debug_vkGetPhysicalDeviceImageFormatProperties2KHR = glad_debug_impl_vkGetPhysicalDeviceImageFormatProperties2KHR;
    glad_debug_vkGetPhysicalDeviceMemoryProperties = glad_debug_impl_vkGetPhysicalDeviceMemoryProperties;
    glad_debug_vkGetPhysicalDeviceMemoryProperties2 = glad_debug_impl_vkGetPhysicalDeviceMemoryProperties2;
    glad_debug_vkGetPhysicalDeviceMemoryProperties2KHR = glad_debug_impl_vkGetPhysicalDeviceMemoryProperties2KHR;
    glad_debug_vkGetPhysicalDevicePresentRectanglesKHR = glad_debug_impl_vkGetPhysicalDevicePresentRectanglesKHR;
    glad_debug_vkGetPhysicalDeviceProperties = glad_debug_impl_vkGetPhysicalDeviceProperties;
    glad_debug_vkGetPhysicalDeviceProperties2 = glad_debug_impl_vkGetPhysicalDeviceProperties2;
    glad_debug_vkGetPhysicalDeviceProperties2KHR = glad_debug_impl_vkGetPhysicalDeviceProperties2KHR;
    glad_debug_vkGetPhysicalDeviceQueueFamilyProperties = glad_debug_impl_vkGetPhysicalDeviceQueueFamilyProperties;
    glad_debug_vkGetPhysicalDeviceQueueFamilyProperties2 = glad_debug_impl_vkGetPhysicalDeviceQueueFamilyProperties2;
    glad_debug_vkGetPhysicalDeviceQueueFamilyProperties2KHR = glad_debug_impl_vkGetPhysicalDeviceQueueFamilyProperties2KHR;
    glad_debug_vkGetPhysicalDeviceSparseImageFormatProperties = glad_debug_impl_vkGetPhysicalDeviceSparseImageFormatProperties;
    glad_debug_vkGetPhysicalDeviceSparseImageFormatProperties2 = glad_debug_impl_vkGetPhysicalDeviceSparseImageFormatProperties2;
    glad_debug_vkGetPhysicalDeviceSparseImageFormatProperties2KHR = glad_debug_impl_vkGetPhysicalDeviceSparseImageFormatProperties2KHR;
    glad_debug_vkGetPhysicalDeviceToolProperties = glad_debug_impl_vkGetPhysicalDeviceToolProperties;
    glad_debug_vkGetPhysicalDeviceToolPropertiesEXT = glad_debug_impl_vkGetPhysicalDeviceToolPropertiesEXT;
    glad_debug_vkGetPipelineCacheData = glad_debug_impl_vkGetPipelineCacheData;
    glad_debug_vkGetPrivateData = glad_debug_impl_vkGetPrivateData;
    glad_debug_vkGetPrivateDataEXT = glad_debug_impl_vkGetPrivateDataEXT;
    glad_debug_vkGetQueryPoolResults = glad_debug_impl_vkGetQueryPoolResults;
    glad_debug_vkGetRenderAreaGranularity = glad_debug_impl_vkGetRenderAreaGranularity;
    glad_debug_vkGetRenderingAreaGranularity = glad_debug_impl_vkGetRenderingAreaGranularity;
    glad_debug_vkGetRenderingAreaGranularityKHR = glad_debug_impl_vkGetRenderingAreaGranularityKHR;
    glad_debug_vkGetSemaphoreCounterValue = glad_debug_impl_vkGetSemaphoreCounterValue;
    glad_debug_vkGetSemaphoreCounterValueKHR = glad_debug_impl_vkGetSemaphoreCounterValueKHR;
    glad_debug_vkGetShaderBinaryDataEXT = glad_debug_impl_vkGetShaderBinaryDataEXT;
    glad_debug_vkInvalidateMappedMemoryRanges = glad_debug_impl_vkInvalidateMappedMemoryRanges;
    glad_debug_vkMapMemory = glad_debug_impl_vkMapMemory;
    glad_debug_vkMapMemory2 = glad_debug_impl_vkMapMemory2;
    glad_debug_vkMapMemory2KHR = glad_debug_impl_vkMapMemory2KHR;
    glad_debug_vkMergePipelineCaches = glad_debug_impl_vkMergePipelineCaches;
    glad_debug_vkQueueBindSparse = glad_debug_impl_vkQueueBindSparse;
    glad_debug_vkQueueSubmit = glad_debug_impl_vkQueueSubmit;
    glad_debug_vkQueueSubmit2 = glad_debug_impl_vkQueueSubmit2;
    glad_debug_vkQueueSubmit2KHR = glad_debug_impl_vkQueueSubmit2KHR;
    glad_debug_vkQueueWaitIdle = glad_debug_impl_vkQueueWaitIdle;
    glad_debug_vkResetCommandBuffer = glad_debug_impl_vkResetCommandBuffer;
    glad_debug_vkResetCommandPool = glad_debug_impl_vkResetCommandPool;
    glad_debug_vkResetDescriptorPool = glad_debug_impl_vkResetDescriptorPool;
    glad_debug_vkResetEvent = glad_debug_impl_vkResetEvent;
    glad_debug_vkResetFences = glad_debug_impl_vkResetFences;
    glad_debug_vkResetQueryPool = glad_debug_impl_vkResetQueryPool;
    glad_debug_vkResetQueryPoolEXT = glad_debug_impl_vkResetQueryPoolEXT;
    glad_debug_vkSetEvent = glad_debug_impl_vkSetEvent;
    glad_debug_vkSetPrivateData = glad_debug_impl_vkSetPrivateData;
    glad_debug_vkSetPrivateDataEXT = glad_debug_impl_vkSetPrivateDataEXT;
    glad_debug_vkSignalSemaphore = glad_debug_impl_vkSignalSemaphore;
    glad_debug_vkSignalSemaphoreKHR = glad_debug_impl_vkSignalSemaphoreKHR;
    glad_debug_vkTransitionImageLayout = glad_debug_impl_vkTransitionImageLayout;
    glad_debug_vkTransitionImageLayoutEXT = glad_debug_impl_vkTransitionImageLayoutEXT;
    glad_debug_vkTrimCommandPool = glad_debug_impl_vkTrimCommandPool;
    glad_debug_vkTrimCommandPoolKHR = glad_debug_impl_vkTrimCommandPoolKHR;
    glad_debug_vkUnmapMemory = glad_debug_impl_vkUnmapMemory;
    glad_debug_vkUnmapMemory2 = glad_debug_impl_vkUnmapMemory2;
    glad_debug_vkUnmapMemory2KHR = glad_debug_impl_vkUnmapMemory2KHR;
    glad_debug_vkUpdateDescriptorSetWithTemplate = glad_debug_impl_vkUpdateDescriptorSetWithTemplate;
    glad_debug_vkUpdateDescriptorSetWithTemplateKHR = glad_debug_impl_vkUpdateDescriptorSetWithTemplateKHR;
    glad_debug_vkUpdateDescriptorSets = glad_debug_impl_vkUpdateDescriptorSets;
    glad_debug_vkWaitForFences = glad_debug_impl_vkWaitForFences;
    glad_debug_vkWaitSemaphores = glad_debug_impl_vkWaitSemaphores;
    glad_debug_vkWaitSemaphoresKHR = glad_debug_impl_vkWaitSemaphoresKHR;
}

void gladUninstallVulkanDebug(void) {
    glad_debug_vkAcquireNextImage2KHR = glad_vkAcquireNextImage2KHR;
    glad_debug_vkAllocateCommandBuffers = glad_vkAllocateCommandBuffers;
    glad_debug_vkAllocateDescriptorSets = glad_vkAllocateDescriptorSets;
    glad_debug_vkAllocateMemory = glad_vkAllocateMemory;
    glad_debug_vkBeginCommandBuffer = glad_vkBeginCommandBuffer;
    glad_debug_vkBindBufferMemory = glad_vkBindBufferMemory;
    glad_debug_vkBindBufferMemory2 = glad_vkBindBufferMemory2;
    glad_debug_vkBindBufferMemory2KHR = glad_vkBindBufferMemory2KHR;
    glad_debug_vkBindImageMemory = glad_vkBindImageMemory;
    glad_debug_vkBindImageMemory2 = glad_vkBindImageMemory2;
    glad_debug_vkBindImageMemory2KHR = glad_vkBindImageMemory2KHR;
    glad_debug_vkCmdBeginQuery = glad_vkCmdBeginQuery;
    glad_debug_vkCmdBeginRenderPass = glad_vkCmdBeginRenderPass;
    glad_debug_vkCmdBeginRenderPass2 = glad_vkCmdBeginRenderPass2;
    glad_debug_vkCmdBeginRenderPass2KHR = glad_vkCmdBeginRenderPass2KHR;
    glad_debug_vkCmdBeginRendering = glad_vkCmdBeginRendering;
    glad_debug_vkCmdBeginRenderingKHR = glad_vkCmdBeginRenderingKHR;
    glad_debug_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT = glad_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT;
    glad_debug_vkCmdBindDescriptorSets = glad_vkCmdBindDescriptorSets;
    glad_debug_vkCmdBindDescriptorSets2 = glad_vkCmdBindDescriptorSets2;
    glad_debug_vkCmdBindDescriptorSets2KHR = glad_vkCmdBindDescriptorSets2KHR;
    glad_debug_vkCmdBindIndexBuffer = glad_vkCmdBindIndexBuffer;
    glad_debug_vkCmdBindIndexBuffer2 = glad_vkCmdBindIndexBuffer2;
    glad_debug_vkCmdBindIndexBuffer2KHR = glad_vkCmdBindIndexBuffer2KHR;
    glad_debug_vkCmdBindPipeline = glad_vkCmdBindPipeline;
    glad_debug_vkCmdBindShadersEXT = glad_vkCmdBindShadersEXT;
    glad_debug_vkCmdBindVertexBuffers = glad_vkCmdBindVertexBuffers;
    glad_debug_vkCmdBindVertexBuffers2 = glad_vkCmdBindVertexBuffers2;
    glad_debug_vkCmdBindVertexBuffers2EXT = glad_vkCmdBindVertexBuffers2EXT;
    glad_debug_vkCmdBlitImage = glad_vkCmdBlitImage;
    glad_debug_vkCmdBlitImage2 = glad_vkCmdBlitImage2;
    glad_debug_vkCmdBlitImage2KHR = glad_vkCmdBlitImage2KHR;
    glad_debug_vkCmdClearAttachments = glad_vkCmdClearAttachments;
    glad_debug_vkCmdClearColorImage = glad_vkCmdClearColorImage;
    glad_debug_vkCmdClearDepthStencilImage = glad_vkCmdClearDepthStencilImage;
    glad_debug_vkCmdCopyBuffer = glad_vkCmdCopyBuffer;
    glad_debug_vkCmdCopyBuffer2 = glad_vkCmdCopyBuffer2;
    glad_debug_vkCmdCopyBuffer2KHR = glad_vkCmdCopyBuffer2KHR;
    glad_debug_vkCmdCopyBufferToImage = glad_vkCmdCopyBufferToImage;
    glad_debug_vkCmdCopyBufferToImage2 = glad_vkCmdCopyBufferToImage2;
    glad_debug_vkCmdCopyBufferToImage2KHR = glad_vkCmdCopyBufferToImage2KHR;
    glad_debug_vkCmdCopyImage = glad_vkCmdCopyImage;
    glad_debug_vkCmdCopyImage2 = glad_vkCmdCopyImage2;
    glad_debug_vkCmdCopyImage2KHR = glad_vkCmdCopyImage2KHR;
    glad_debug_vkCmdCopyImageToBuffer = glad_vkCmdCopyImageToBuffer;
    glad_debug_vkCmdCopyImageToBuffer2 = glad_vkCmdCopyImageToBuffer2;
    glad_debug_vkCmdCopyImageToBuffer2KHR = glad_vkCmdCopyImageToBuffer2KHR;
    glad_debug_vkCmdCopyQueryPoolResults = glad_vkCmdCopyQueryPoolResults;
    glad_debug_vkCmdDispatch = glad_vkCmdDispatch;
    glad_debug_vkCmdDispatchBase = glad_vkCmdDispatchBase;
    glad_debug_vkCmdDispatchBaseKHR = glad_vkCmdDispatchBaseKHR;
    glad_debug_vkCmdDispatchIndirect = glad_vkCmdDispatchIndirect;
    glad_debug_vkCmdDraw = glad_vkCmdDraw;
    glad_debug_vkCmdDrawIndexed = glad_vkCmdDrawIndexed;
    glad_debug_vkCmdDrawIndexedIndirect = glad_vkCmdDrawIndexedIndirect;
    glad_debug_vkCmdDrawIndexedIndirectCount = glad_vkCmdDrawIndexedIndirectCount;
    glad_debug_vkCmdDrawIndexedIndirectCountAMD = glad_vkCmdDrawIndexedIndirectCountAMD;
    glad_debug_vkCmdDrawIndexedIndirectCountKHR = glad_vkCmdDrawIndexedIndirectCountKHR;
    glad_debug_vkCmdDrawIndirect = glad_vkCmdDrawIndirect;
    glad_debug_vkCmdDrawIndirectCount = glad_vkCmdDrawIndirectCount;
    glad_debug_vkCmdDrawIndirectCountAMD = glad_vkCmdDrawIndirectCountAMD;
    glad_debug_vkCmdDrawIndirectCountKHR = glad_vkCmdDrawIndirectCountKHR;
    glad_debug_vkCmdEndQuery = glad_vkCmdEndQuery;
    glad_debug_vkCmdEndRenderPass = glad_vkCmdEndRenderPass;
    glad_debug_vkCmdEndRenderPass2 = glad_vkCmdEndRenderPass2;
    glad_debug_vkCmdEndRenderPass2KHR = glad_vkCmdEndRenderPass2KHR;
    glad_debug_vkCmdEndRendering = glad_vkCmdEndRendering;
    glad_debug_vkCmdEndRenderingKHR = glad_vkCmdEndRenderingKHR;
    glad_debug_vkCmdExecuteCommands = glad_vkCmdExecuteCommands;
    glad_debug_vkCmdFillBuffer = glad_vkCmdFillBuffer;
    glad_debug_vkCmdNextSubpass = glad_vkCmdNextSubpass;
    glad_debug_vkCmdNextSubpass2 = glad_vkCmdNextSubpass2;
    glad_debug_vkCmdNextSubpass2KHR = glad_vkCmdNextSubpass2KHR;
    glad_debug_vkCmdPipelineBarrier = glad_vkCmdPipelineBarrier;
    glad_debug_vkCmdPipelineBarrier2 = glad_vkCmdPipelineBarrier2;
    glad_debug_vkCmdPipelineBarrier2KHR = glad_vkCmdPipelineBarrier2KHR;
    glad_debug_vkCmdPushConstants = glad_vkCmdPushConstants;
    glad_debug_vkCmdPushConstants2 = glad_vkCmdPushConstants2;
    glad_debug_vkCmdPushConstants2KHR = glad_vkCmdPushConstants2KHR;
    glad_debug_vkCmdPushDescriptorSet = glad_vkCmdPushDescriptorSet;
    glad_debug_vkCmdPushDescriptorSet2 = glad_vkCmdPushDescriptorSet2;
    glad_debug_vkCmdPushDescriptorSet2KHR = glad_vkCmdPushDescriptorSet2KHR;
    glad_debug_vkCmdPushDescriptorSetKHR = glad_vkCmdPushDescriptorSetKHR;
    glad_debug_vkCmdPushDescriptorSetWithTemplate = glad_vkCmdPushDescriptorSetWithTemplate;
    glad_debug_vkCmdPushDescriptorSetWithTemplate2 = glad_vkCmdPushDescriptorSetWithTemplate2;
    glad_debug_vkCmdPushDescriptorSetWithTemplate2KHR = glad_vkCmdPushDescriptorSetWithTemplate2KHR;
    glad_debug_vkCmdPushDescriptorSetWithTemplateKHR = glad_vkCmdPushDescriptorSetWithTemplateKHR;
    glad_debug_vkCmdResetEvent = glad_vkCmdResetEvent;
    glad_debug_vkCmdResetEvent2 = glad_vkCmdResetEvent2;
    glad_debug_vkCmdResetEvent2KHR = glad_vkCmdResetEvent2KHR;
    glad_debug_vkCmdResetQueryPool = glad_vkCmdResetQueryPool;
    glad_debug_vkCmdResolveImage = glad_vkCmdResolveImage;
    glad_debug_vkCmdResolveImage2 = glad_vkCmdResolveImage2;
    glad_debug_vkCmdResolveImage2KHR = glad_vkCmdResolveImage2KHR;
    glad_debug_vkCmdSetAlphaToCoverageEnableEXT = glad_vkCmdSetAlphaToCoverageEnableEXT;
    glad_debug_vkCmdSetAlphaToOneEnableEXT = glad_vkCmdSetAlphaToOneEnableEXT;
    glad_debug_vkCmdSetBlendConstants = glad_vkCmdSetBlendConstants;
    glad_debug_vkCmdSetColorBlendAdvancedEXT = glad_vkCmdSetColorBlendAdvancedEXT;
    glad_debug_vkCmdSetColorBlendEnableEXT = glad_vkCmdSetColorBlendEnableEXT;
    glad_debug_vkCmdSetColorBlendEquationEXT = glad_vkCmdSetColorBlendEquationEXT;
    glad_debug_vkCmdSetColorWriteMaskEXT = glad_vkCmdSetColorWriteMaskEXT;
    glad_debug_vkCmdSetConservativeRasterizationModeEXT = glad_vkCmdSetConservativeRasterizationModeEXT;
    glad_debug_vkCmdSetCoverageModulationModeNV = glad_vkCmdSetCoverageModulationModeNV;
    glad_debug_vkCmdSetCoverageModulationTableEnableNV = glad_vkCmdSetCoverageModulationTableEnableNV;
    glad_debug_vkCmdSetCoverageModulationTableNV = glad_vkCmdSetCoverageModulationTableNV;
    glad_debug_vkCmdSetCoverageReductionModeNV = glad_vkCmdSetCoverageReductionModeNV;
    glad_debug_vkCmdSetCoverageToColorEnableNV = glad_vkCmdSetCoverageToColorEnableNV;
    glad_debug_vkCmdSetCoverageToColorLocationNV = glad_vkCmdSetCoverageToColorLocationNV;
    glad_debug_vkCmdSetCullMode = glad_vkCmdSetCullMode;
    glad_debug_vkCmdSetCullModeEXT = glad_vkCmdSetCullModeEXT;
    glad_debug_vkCmdSetDepthBias = glad_vkCmdSetDepthBias;
    glad_debug_vkCmdSetDepthBiasEnable = glad_vkCmdSetDepthBiasEnable;
    glad_debug_vkCmdSetDepthBiasEnableEXT = glad_vkCmdSetDepthBiasEnableEXT;
    glad_debug_vkCmdSetDepthBounds = glad_vkCmdSetDepthBounds;
    glad_debug_vkCmdSetDepthBoundsTestEnable = glad_vkCmdSetDepthBoundsTestEnable;
    glad_debug_vkCmdSetDepthBoundsTestEnableEXT = glad_vkCmdSetDepthBoundsTestEnableEXT;
    glad_debug_vkCmdSetDepthClampEnableEXT = glad_vkCmdSetDepthClampEnableEXT;
    glad_debug_vkCmdSetDepthClampRangeEXT = glad_vkCmdSetDepthClampRangeEXT;
    glad_debug_vkCmdSetDepthClipEnableEXT = glad_vkCmdSetDepthClipEnableEXT;
    glad_debug_vkCmdSetDepthClipNegativeOneToOneEXT = glad_vkCmdSetDepthClipNegativeOneToOneEXT;
    glad_debug_vkCmdSetDepthCompareOp = glad_vkCmdSetDepthCompareOp;
    glad_debug_vkCmdSetDepthCompareOpEXT = glad_vkCmdSetDepthCompareOpEXT;
    glad_debug_vkCmdSetDepthTestEnable = glad_vkCmdSetDepthTestEnable;
    glad_debug_vkCmdSetDepthTestEnableEXT = glad_vkCmdSetDepthTestEnableEXT;
    glad_debug_vkCmdSetDepthWriteEnable = glad_vkCmdSetDepthWriteEnable;
    glad_debug_vkCmdSetDepthWriteEnableEXT = glad_vkCmdSetDepthWriteEnableEXT;
    glad_debug_vkCmdSetDescriptorBufferOffsets2EXT = glad_vkCmdSetDescriptorBufferOffsets2EXT;
    glad_debug_vkCmdSetDeviceMask = glad_vkCmdSetDeviceMask;
    glad_debug_vkCmdSetDeviceMaskKHR = glad_vkCmdSetDeviceMaskKHR;
    glad_debug_vkCmdSetEvent = glad_vkCmdSetEvent;
    glad_debug_vkCmdSetEvent2 = glad_vkCmdSetEvent2;
    glad_debug_vkCmdSetEvent2KHR = glad_vkCmdSetEvent2KHR;
    glad_debug_vkCmdSetExtraPrimitiveOverestimationSizeEXT = glad_vkCmdSetExtraPrimitiveOverestimationSizeEXT;
    glad_debug_vkCmdSetFrontFace = glad_vkCmdSetFrontFace;
    glad_debug_vkCmdSetFrontFaceEXT = glad_vkCmdSetFrontFaceEXT;
    glad_debug_vkCmdSetLineRasterizationModeEXT = glad_vkCmdSetLineRasterizationModeEXT;
    glad_debug_vkCmdSetLineStipple = glad_vkCmdSetLineStipple;
    glad_debug_vkCmdSetLineStippleEXT = glad_vkCmdSetLineStippleEXT;
    glad_debug_vkCmdSetLineStippleEnableEXT = glad_vkCmdSetLineStippleEnableEXT;
    glad_debug_vkCmdSetLineStippleKHR = glad_vkCmdSetLineStippleKHR;
    glad_debug_vkCmdSetLineWidth = glad_vkCmdSetLineWidth;
    glad_debug_vkCmdSetLogicOpEXT = glad_vkCmdSetLogicOpEXT;
    glad_debug_vkCmdSetLogicOpEnableEXT = glad_vkCmdSetLogicOpEnableEXT;
    glad_debug_vkCmdSetPatchControlPointsEXT = glad_vkCmdSetPatchControlPointsEXT;
    glad_debug_vkCmdSetPolygonModeEXT = glad_vkCmdSetPolygonModeEXT;
    glad_debug_vkCmdSetPrimitiveRestartEnable = glad_vkCmdSetPrimitiveRestartEnable;
    glad_debug_vkCmdSetPrimitiveRestartEnableEXT = glad_vkCmdSetPrimitiveRestartEnableEXT;
    glad_debug_vkCmdSetPrimitiveTopology = glad_vkCmdSetPrimitiveTopology;
    glad_debug_vkCmdSetPrimitiveTopologyEXT = glad_vkCmdSetPrimitiveTopologyEXT;
    glad_debug_vkCmdSetProvokingVertexModeEXT = glad_vkCmdSetProvokingVertexModeEXT;
    glad_debug_vkCmdSetRasterizationSamplesEXT = glad_vkCmdSetRasterizationSamplesEXT;
    glad_debug_vkCmdSetRasterizationStreamEXT = glad_vkCmdSetRasterizationStreamEXT;
    glad_debug_vkCmdSetRasterizerDiscardEnable = glad_vkCmdSetRasterizerDiscardEnable;
    glad_debug_vkCmdSetRasterizerDiscardEnableEXT = glad_vkCmdSetRasterizerDiscardEnableEXT;
    glad_debug_vkCmdSetRenderingAttachmentLocations = glad_vkCmdSetRenderingAttachmentLocations;
    glad_debug_vkCmdSetRenderingAttachmentLocationsKHR = glad_vkCmdSetRenderingAttachmentLocationsKHR;
    glad_debug_vkCmdSetRenderingInputAttachmentIndices = glad_vkCmdSetRenderingInputAttachmentIndices;
    glad_debug_vkCmdSetRenderingInputAttachmentIndicesKHR = glad_vkCmdSetRenderingInputAttachmentIndicesKHR;
    glad_debug_vkCmdSetRepresentativeFragmentTestEnableNV = glad_vkCmdSetRepresentativeFragmentTestEnableNV;
    glad_debug_vkCmdSetSampleLocationsEnableEXT = glad_vkCmdSetSampleLocationsEnableEXT;
    glad_debug_vkCmdSetSampleMaskEXT = glad_vkCmdSetSampleMaskEXT;
    glad_debug_vkCmdSetScissor = glad_vkCmdSetScissor;
    glad_debug_vkCmdSetScissorWithCount = glad_vkCmdSetScissorWithCount;
    glad_debug_vkCmdSetScissorWithCountEXT = glad_vkCmdSetScissorWithCountEXT;
    glad_debug_vkCmdSetShadingRateImageEnableNV = glad_vkCmdSetShadingRateImageEnableNV;
    glad_debug_vkCmdSetStencilCompareMask = glad_vkCmdSetStencilCompareMask;
    glad_debug_vkCmdSetStencilOp = glad_vkCmdSetStencilOp;
    glad_debug_vkCmdSetStencilOpEXT = glad_vkCmdSetStencilOpEXT;
    glad_debug_vkCmdSetStencilReference = glad_vkCmdSetStencilReference;
    glad_debug_vkCmdSetStencilTestEnable = glad_vkCmdSetStencilTestEnable;
    glad_debug_vkCmdSetStencilTestEnableEXT = glad_vkCmdSetStencilTestEnableEXT;
    glad_debug_vkCmdSetStencilWriteMask = glad_vkCmdSetStencilWriteMask;
    glad_debug_vkCmdSetTessellationDomainOriginEXT = glad_vkCmdSetTessellationDomainOriginEXT;
    glad_debug_vkCmdSetVertexInputEXT = glad_vkCmdSetVertexInputEXT;
    glad_debug_vkCmdSetViewport = glad_vkCmdSetViewport;
    glad_debug_vkCmdSetViewportSwizzleNV = glad_vkCmdSetViewportSwizzleNV;
    glad_debug_vkCmdSetViewportWScalingEnableNV = glad_vkCmdSetViewportWScalingEnableNV;
    glad_debug_vkCmdSetViewportWithCount = glad_vkCmdSetViewportWithCount;
    glad_debug_vkCmdSetViewportWithCountEXT = glad_vkCmdSetViewportWithCountEXT;
    glad_debug_vkCmdUpdateBuffer = glad_vkCmdUpdateBuffer;
    glad_debug_vkCmdWaitEvents = glad_vkCmdWaitEvents;
    glad_debug_vkCmdWaitEvents2 = glad_vkCmdWaitEvents2;
    glad_debug_vkCmdWaitEvents2KHR = glad_vkCmdWaitEvents2KHR;
    glad_debug_vkCmdWriteTimestamp = glad_vkCmdWriteTimestamp;
    glad_debug_vkCmdWriteTimestamp2 = glad_vkCmdWriteTimestamp2;
    glad_debug_vkCmdWriteTimestamp2KHR = glad_vkCmdWriteTimestamp2KHR;
    glad_debug_vkCopyImageToImage = glad_vkCopyImageToImage;
    glad_debug_vkCopyImageToImageEXT = glad_vkCopyImageToImageEXT;
    glad_debug_vkCopyImageToMemory = glad_vkCopyImageToMemory;
    glad_debug_vkCopyImageToMemoryEXT = glad_vkCopyImageToMemoryEXT;
    glad_debug_vkCopyMemoryToImage = glad_vkCopyMemoryToImage;
    glad_debug_vkCopyMemoryToImageEXT = glad_vkCopyMemoryToImageEXT;
    glad_debug_vkCreateBuffer = glad_vkCreateBuffer;
    glad_debug_vkCreateBufferView = glad_vkCreateBufferView;
    glad_debug_vkCreateCommandPool = glad_vkCreateCommandPool;
    glad_debug_vkCreateComputePipelines = glad_vkCreateComputePipelines;
    glad_debug_vkCreateDescriptorPool = glad_vkCreateDescriptorPool;
    glad_debug_vkCreateDescriptorSetLayout = glad_vkCreateDescriptorSetLayout;
    glad_debug_vkCreateDescriptorUpdateTemplate = glad_vkCreateDescriptorUpdateTemplate;
    glad_debug_vkCreateDescriptorUpdateTemplateKHR = glad_vkCreateDescriptorUpdateTemplateKHR;
    glad_debug_vkCreateDevice = glad_vkCreateDevice;
    glad_debug_vkCreateEvent = glad_vkCreateEvent;
    glad_debug_vkCreateFence = glad_vkCreateFence;
    glad_debug_vkCreateFramebuffer = glad_vkCreateFramebuffer;
    glad_debug_vkCreateGraphicsPipelines = glad_vkCreateGraphicsPipelines;
    glad_debug_vkCreateImage = glad_vkCreateImage;
    glad_debug_vkCreateImageView = glad_vkCreateImageView;
    glad_debug_vkCreateInstance = glad_vkCreateInstance;
    glad_debug_vkCreatePipelineCache = glad_vkCreatePipelineCache;
    glad_debug_vkCreatePipelineLayout = glad_vkCreatePipelineLayout;
    glad_debug_vkCreatePrivateDataSlot = glad_vkCreatePrivateDataSlot;
    glad_debug_vkCreatePrivateDataSlotEXT = glad_vkCreatePrivateDataSlotEXT;
    glad_debug_vkCreateQueryPool = glad_vkCreateQueryPool;
    glad_debug_vkCreateRenderPass = glad_vkCreateRenderPass;
    glad_debug_vkCreateRenderPass2 = glad_vkCreateRenderPass2;
    glad_debug_vkCreateRenderPass2KHR = glad_vkCreateRenderPass2KHR;
    glad_debug_vkCreateSampler = glad_vkCreateSampler;
    glad_debug_vkCreateSamplerYcbcrConversion = glad_vkCreateSamplerYcbcrConversion;
    glad_debug_vkCreateSamplerYcbcrConversionKHR = glad_vkCreateSamplerYcbcrConversionKHR;
    glad_debug_vkCreateSemaphore = glad_vkCreateSemaphore;
    glad_debug_vkCreateShaderModule = glad_vkCreateShaderModule;
    glad_debug_vkCreateShadersEXT = glad_vkCreateShadersEXT;
    glad_debug_vkDestroyBuffer = glad_vkDestroyBuffer;
    glad_debug_vkDestroyBufferView = glad_vkDestroyBufferView;
    glad_debug_vkDestroyCommandPool = glad_vkDestroyCommandPool;
    glad_debug_vkDestroyDescriptorPool = glad_vkDestroyDescriptorPool;
    glad_debug_vkDestroyDescriptorSetLayout = glad_vkDestroyDescriptorSetLayout;
    glad_debug_vkDestroyDescriptorUpdateTemplate = glad_vkDestroyDescriptorUpdateTemplate;
    glad_debug_vkDestroyDescriptorUpdateTemplateKHR = glad_vkDestroyDescriptorUpdateTemplateKHR;
    glad_debug_vkDestroyDevice = glad_vkDestroyDevice;
    glad_debug_vkDestroyEvent = glad_vkDestroyEvent;
    glad_debug_vkDestroyFence = glad_vkDestroyFence;
    glad_debug_vkDestroyFramebuffer = glad_vkDestroyFramebuffer;
    glad_debug_vkDestroyImage = glad_vkDestroyImage;
    glad_debug_vkDestroyImageView = glad_vkDestroyImageView;
    glad_debug_vkDestroyInstance = glad_vkDestroyInstance;
    glad_debug_vkDestroyPipeline = glad_vkDestroyPipeline;
    glad_debug_vkDestroyPipelineCache = glad_vkDestroyPipelineCache;
    glad_debug_vkDestroyPipelineLayout = glad_vkDestroyPipelineLayout;
    glad_debug_vkDestroyPrivateDataSlot = glad_vkDestroyPrivateDataSlot;
    glad_debug_vkDestroyPrivateDataSlotEXT = glad_vkDestroyPrivateDataSlotEXT;
    glad_debug_vkDestroyQueryPool = glad_vkDestroyQueryPool;
    glad_debug_vkDestroyRenderPass = glad_vkDestroyRenderPass;
    glad_debug_vkDestroySampler = glad_vkDestroySampler;
    glad_debug_vkDestroySamplerYcbcrConversion = glad_vkDestroySamplerYcbcrConversion;
    glad_debug_vkDestroySamplerYcbcrConversionKHR = glad_vkDestroySamplerYcbcrConversionKHR;
    glad_debug_vkDestroySemaphore = glad_vkDestroySemaphore;
    glad_debug_vkDestroyShaderEXT = glad_vkDestroyShaderEXT;
    glad_debug_vkDestroyShaderModule = glad_vkDestroyShaderModule;
    glad_debug_vkDeviceWaitIdle = glad_vkDeviceWaitIdle;
    glad_debug_vkEndCommandBuffer = glad_vkEndCommandBuffer;
    glad_debug_vkEnumerateDeviceExtensionProperties = glad_vkEnumerateDeviceExtensionProperties;
    glad_debug_vkEnumerateDeviceLayerProperties = glad_vkEnumerateDeviceLayerProperties;
    glad_debug_vkEnumerateInstanceExtensionProperties = glad_vkEnumerateInstanceExtensionProperties;
    glad_debug_vkEnumerateInstanceLayerProperties = glad_vkEnumerateInstanceLayerProperties;
    glad_debug_vkEnumerateInstanceVersion = glad_vkEnumerateInstanceVersion;
    glad_debug_vkEnumeratePhysicalDeviceGroups = glad_vkEnumeratePhysicalDeviceGroups;
    glad_debug_vkEnumeratePhysicalDeviceGroupsKHR = glad_vkEnumeratePhysicalDeviceGroupsKHR;
    glad_debug_vkEnumeratePhysicalDevices = glad_vkEnumeratePhysicalDevices;
    glad_debug_vkFlushMappedMemoryRanges = glad_vkFlushMappedMemoryRanges;
    glad_debug_vkFreeCommandBuffers = glad_vkFreeCommandBuffers;
    glad_debug_vkFreeDescriptorSets = glad_vkFreeDescriptorSets;
    glad_debug_vkFreeMemory = glad_vkFreeMemory;
    glad_debug_vkGetBufferDeviceAddress = glad_vkGetBufferDeviceAddress;
    glad_debug_vkGetBufferDeviceAddressEXT = glad_vkGetBufferDeviceAddressEXT;
    glad_debug_vkGetBufferDeviceAddressKHR = glad_vkGetBufferDeviceAddressKHR;
    glad_debug_vkGetBufferMemoryRequirements = glad_vkGetBufferMemoryRequirements;
    glad_debug_vkGetBufferMemoryRequirements2 = glad_vkGetBufferMemoryRequirements2;
    glad_debug_vkGetBufferMemoryRequirements2KHR = glad_vkGetBufferMemoryRequirements2KHR;
    glad_debug_vkGetBufferOpaqueCaptureAddress = glad_vkGetBufferOpaqueCaptureAddress;
    glad_debug_vkGetBufferOpaqueCaptureAddressKHR = glad_vkGetBufferOpaqueCaptureAddressKHR;
    glad_debug_vkGetDescriptorSetLayoutSupport = glad_vkGetDescriptorSetLayoutSupport;
    glad_debug_vkGetDescriptorSetLayoutSupportKHR = glad_vkGetDescriptorSetLayoutSupportKHR;
    glad_debug_vkGetDeviceBufferMemoryRequirements = glad_vkGetDeviceBufferMemoryRequirements;
    glad_debug_vkGetDeviceBufferMemoryRequirementsKHR = glad_vkGetDeviceBufferMemoryRequirementsKHR;
    glad_debug_vkGetDeviceGroupPeerMemoryFeatures = glad_vkGetDeviceGroupPeerMemoryFeatures;
    glad_debug_vkGetDeviceGroupPeerMemoryFeaturesKHR = glad_vkGetDeviceGroupPeerMemoryFeaturesKHR;
    glad_debug_vkGetDeviceGroupPresentCapabilitiesKHR = glad_vkGetDeviceGroupPresentCapabilitiesKHR;
    glad_debug_vkGetDeviceGroupSurfacePresentModesKHR = glad_vkGetDeviceGroupSurfacePresentModesKHR;
    glad_debug_vkGetDeviceImageMemoryRequirements = glad_vkGetDeviceImageMemoryRequirements;
    glad_debug_vkGetDeviceImageMemoryRequirementsKHR = glad_vkGetDeviceImageMemoryRequirementsKHR;
    glad_debug_vkGetDeviceImageSparseMemoryRequirements = glad_vkGetDeviceImageSparseMemoryRequirements;
    glad_debug_vkGetDeviceImageSparseMemoryRequirementsKHR = glad_vkGetDeviceImageSparseMemoryRequirementsKHR;
    glad_debug_vkGetDeviceImageSubresourceLayout = glad_vkGetDeviceImageSubresourceLayout;
    glad_debug_vkGetDeviceImageSubresourceLayoutKHR = glad_vkGetDeviceImageSubresourceLayoutKHR;
    glad_debug_vkGetDeviceMemoryCommitment = glad_vkGetDeviceMemoryCommitment;
    glad_debug_vkGetDeviceMemoryOpaqueCaptureAddress = glad_vkGetDeviceMemoryOpaqueCaptureAddress;
    glad_debug_vkGetDeviceMemoryOpaqueCaptureAddressKHR = glad_vkGetDeviceMemoryOpaqueCaptureAddressKHR;
    glad_debug_vkGetDeviceProcAddr = glad_vkGetDeviceProcAddr;
    glad_debug_vkGetDeviceQueue = glad_vkGetDeviceQueue;
    glad_debug_vkGetDeviceQueue2 = glad_vkGetDeviceQueue2;
    glad_debug_vkGetEventStatus = glad_vkGetEventStatus;
    glad_debug_vkGetFenceStatus = glad_vkGetFenceStatus;
    glad_debug_vkGetImageMemoryRequirements = glad_vkGetImageMemoryRequirements;
    glad_debug_vkGetImageMemoryRequirements2 = glad_vkGetImageMemoryRequirements2;
    glad_debug_vkGetImageMemoryRequirements2KHR = glad_vkGetImageMemoryRequirements2KHR;
    glad_debug_vkGetImageSparseMemoryRequirements = glad_vkGetImageSparseMemoryRequirements;
    glad_debug_vkGetImageSparseMemoryRequirements2 = glad_vkGetImageSparseMemoryRequirements2;
    glad_debug_vkGetImageSparseMemoryRequirements2KHR = glad_vkGetImageSparseMemoryRequirements2KHR;
    glad_debug_vkGetImageSubresourceLayout = glad_vkGetImageSubresourceLayout;
    glad_debug_vkGetImageSubresourceLayout2 = glad_vkGetImageSubresourceLayout2;
    glad_debug_vkGetImageSubresourceLayout2EXT = glad_vkGetImageSubresourceLayout2EXT;
    glad_debug_vkGetImageSubresourceLayout2KHR = glad_vkGetImageSubresourceLayout2KHR;
    glad_debug_vkGetInstanceProcAddr = glad_vkGetInstanceProcAddr;
    glad_debug_vkGetPhysicalDeviceExternalBufferProperties = glad_vkGetPhysicalDeviceExternalBufferProperties;
    glad_debug_vkGetPhysicalDeviceExternalBufferPropertiesKHR = glad_vkGetPhysicalDeviceExternalBufferPropertiesKHR;
    glad_debug_vkGetPhysicalDeviceExternalFenceProperties = glad_vkGetPhysicalDeviceExternalFenceProperties;
    glad_debug_vkGetPhysicalDeviceExternalFencePropertiesKHR = glad_vkGetPhysicalDeviceExternalFencePropertiesKHR;
    glad_debug_vkGetPhysicalDeviceExternalSemaphoreProperties = glad_vkGetPhysicalDeviceExternalSemaphoreProperties;
    glad_debug_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = glad_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR;
    glad_debug_vkGetPhysicalDeviceFeatures = glad_vkGetPhysicalDeviceFeatures;
    glad_debug_vkGetPhysicalDeviceFeatures2 = glad_vkGetPhysicalDeviceFeatures2;
    glad_debug_vkGetPhysicalDeviceFeatures2KHR = glad_vkGetPhysicalDeviceFeatures2KHR;
    glad_debug_vkGetPhysicalDeviceFormatProperties = glad_vkGetPhysicalDeviceFormatProperties;
    glad_debug_vkGetPhysicalDeviceFormatProperties2 = glad_vkGetPhysicalDeviceFormatProperties2;
    glad_debug_vkGetPhysicalDeviceFormatProperties2KHR = glad_vkGetPhysicalDeviceFormatProperties2KHR;
    glad_debug_vkGetPhysicalDeviceImageFormatProperties = glad_vkGetPhysicalDeviceImageFormatProperties;
    glad_debug_vkGetPhysicalDeviceImageFormatProperties2 = glad_vkGetPhysicalDeviceImageFormatProperties2;
    glad_debug_vkGetPhysicalDeviceImageFormatProperties2KHR = glad_vkGetPhysicalDeviceImageFormatProperties2KHR;
    glad_debug_vkGetPhysicalDeviceMemoryProperties = glad_vkGetPhysicalDeviceMemoryProperties;
    glad_debug_vkGetPhysicalDeviceMemoryProperties2 = glad_vkGetPhysicalDeviceMemoryProperties2;
    glad_debug_vkGetPhysicalDeviceMemoryProperties2KHR = glad_vkGetPhysicalDeviceMemoryProperties2KHR;
    glad_debug_vkGetPhysicalDevicePresentRectanglesKHR = glad_vkGetPhysicalDevicePresentRectanglesKHR;
    glad_debug_vkGetPhysicalDeviceProperties = glad_vkGetPhysicalDeviceProperties;
    glad_debug_vkGetPhysicalDeviceProperties2 = glad_vkGetPhysicalDeviceProperties2;
    glad_debug_vkGetPhysicalDeviceProperties2KHR = glad_vkGetPhysicalDeviceProperties2KHR;
    glad_debug_vkGetPhysicalDeviceQueueFamilyProperties = glad_vkGetPhysicalDeviceQueueFamilyProperties;
    glad_debug_vkGetPhysicalDeviceQueueFamilyProperties2 = glad_vkGetPhysicalDeviceQueueFamilyProperties2;
    glad_debug_vkGetPhysicalDeviceQueueFamilyProperties2KHR = glad_vkGetPhysicalDeviceQueueFamilyProperties2KHR;
    glad_debug_vkGetPhysicalDeviceSparseImageFormatProperties = glad_vkGetPhysicalDeviceSparseImageFormatProperties;
    glad_debug_vkGetPhysicalDeviceSparseImageFormatProperties2 = glad_vkGetPhysicalDeviceSparseImageFormatProperties2;
    glad_debug_vkGetPhysicalDeviceSparseImageFormatProperties2KHR = glad_vkGetPhysicalDeviceSparseImageFormatProperties2KHR;
    glad_debug_vkGetPhysicalDeviceToolProperties = glad_vkGetPhysicalDeviceToolProperties;
    glad_debug_vkGetPhysicalDeviceToolPropertiesEXT = glad_vkGetPhysicalDeviceToolPropertiesEXT;
    glad_debug_vkGetPipelineCacheData = glad_vkGetPipelineCacheData;
    glad_debug_vkGetPrivateData = glad_vkGetPrivateData;
    glad_debug_vkGetPrivateDataEXT = glad_vkGetPrivateDataEXT;
    glad_debug_vkGetQueryPoolResults = glad_vkGetQueryPoolResults;
    glad_debug_vkGetRenderAreaGranularity = glad_vkGetRenderAreaGranularity;
    glad_debug_vkGetRenderingAreaGranularity = glad_vkGetRenderingAreaGranularity;
    glad_debug_vkGetRenderingAreaGranularityKHR = glad_vkGetRenderingAreaGranularityKHR;
    glad_debug_vkGetSemaphoreCounterValue = glad_vkGetSemaphoreCounterValue;
    glad_debug_vkGetSemaphoreCounterValueKHR = glad_vkGetSemaphoreCounterValueKHR;
    glad_debug_vkGetShaderBinaryDataEXT = glad_vkGetShaderBinaryDataEXT;
    glad_debug_vkInvalidateMappedMemoryRanges = glad_vkInvalidateMappedMemoryRanges;
    glad_debug_vkMapMemory = glad_vkMapMemory;
    glad_debug_vkMapMemory2 = glad_vkMapMemory2;
    glad_debug_vkMapMemory2KHR = glad_vkMapMemory2KHR;
    glad_debug_vkMergePipelineCaches = glad_vkMergePipelineCaches;
    glad_debug_vkQueueBindSparse = glad_vkQueueBindSparse;
    glad_debug_vkQueueSubmit = glad_vkQueueSubmit;
    glad_debug_vkQueueSubmit2 = glad_vkQueueSubmit2;
    glad_debug_vkQueueSubmit2KHR = glad_vkQueueSubmit2KHR;
    glad_debug_vkQueueWaitIdle = glad_vkQueueWaitIdle;
    glad_debug_vkResetCommandBuffer = glad_vkResetCommandBuffer;
    glad_debug_vkResetCommandPool = glad_vkResetCommandPool;
    glad_debug_vkResetDescriptorPool = glad_vkResetDescriptorPool;
    glad_debug_vkResetEvent = glad_vkResetEvent;
    glad_debug_vkResetFences = glad_vkResetFences;
    glad_debug_vkResetQueryPool = glad_vkResetQueryPool;
    glad_debug_vkResetQueryPoolEXT = glad_vkResetQueryPoolEXT;
    glad_debug_vkSetEvent = glad_vkSetEvent;
    glad_debug_vkSetPrivateData = glad_vkSetPrivateData;
    glad_debug_vkSetPrivateDataEXT = glad_vkSetPrivateDataEXT;
    glad_debug_vkSignalSemaphore = glad_vkSignalSemaphore;
    glad_debug_vkSignalSemaphoreKHR = glad_vkSignalSemaphoreKHR;
    glad_debug_vkTransitionImageLayout = glad_vkTransitionImageLayout;
    glad_debug_vkTransitionImageLayoutEXT = glad_vkTransitionImageLayoutEXT;
    glad_debug_vkTrimCommandPool = glad_vkTrimCommandPool;
    glad_debug_vkTrimCommandPoolKHR = glad_vkTrimCommandPoolKHR;
    glad_debug_vkUnmapMemory = glad_vkUnmapMemory;
    glad_debug_vkUnmapMemory2 = glad_vkUnmapMemory2;
    glad_debug_vkUnmapMemory2KHR = glad_vkUnmapMemory2KHR;
    glad_debug_vkUpdateDescriptorSetWithTemplate = glad_vkUpdateDescriptorSetWithTemplate;
    glad_debug_vkUpdateDescriptorSetWithTemplateKHR = glad_vkUpdateDescriptorSetWithTemplateKHR;
    glad_debug_vkUpdateDescriptorSets = glad_vkUpdateDescriptorSets;
    glad_debug_vkWaitForFences = glad_vkWaitForFences;
    glad_debug_vkWaitSemaphores = glad_vkWaitSemaphores;
    glad_debug_vkWaitSemaphoresKHR = glad_vkWaitSemaphoresKHR;
}

#ifdef GLAD_VULKAN

#ifndef GLAD_LOADER_LIBRARY_C_
#define GLAD_LOADER_LIBRARY_C_

#include <stddef.h>
#include <stdlib.h>

#if GLAD_PLATFORM_WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif


static void* glad_get_dlopen_handle(const char *lib_names[], int length) {
    void *handle = NULL;
    int i;

    for (i = 0; i < length; ++i) {
#if GLAD_PLATFORM_WIN32
  #if GLAD_PLATFORM_UWP
        size_t buffer_size = (strlen(lib_names[i]) + 1) * sizeof(WCHAR);
        LPWSTR buffer = (LPWSTR) malloc(buffer_size);
        if (buffer != NULL) {
            int ret = MultiByteToWideChar(CP_ACP, 0, lib_names[i], -1, buffer, buffer_size);
            if (ret != 0) {
                handle = (void*) LoadPackagedLibrary(buffer, 0);
            }
            free((void*) buffer);
        }
  #else
        handle = (void*) LoadLibraryA(lib_names[i]);
  #endif
#else
        handle = dlopen(lib_names[i], RTLD_LAZY | RTLD_LOCAL);
#endif
        if (handle != NULL) {
            return handle;
        }
    }

    return NULL;
}

static void glad_close_dlopen_handle(void* handle) {
    if (handle != NULL) {
#if GLAD_PLATFORM_WIN32
        FreeLibrary((HMODULE) handle);
#else
        dlclose(handle);
#endif
    }
}

static GLADapiproc glad_dlsym_handle(void* handle, const char *name) {
    if (handle == NULL) {
        return NULL;
    }

#if GLAD_PLATFORM_WIN32
    return (GLADapiproc) GetProcAddress((HMODULE) handle, name);
#else
    return GLAD_GNUC_EXTENSION (GLADapiproc) dlsym(handle, name);
#endif
}

#endif /* GLAD_LOADER_LIBRARY_C_ */


static const char* DEVICE_FUNCTIONS[] = {
    "vkAcquireNextImage2KHR",
    "vkAllocateCommandBuffers",
    "vkAllocateDescriptorSets",
    "vkAllocateMemory",
    "vkBeginCommandBuffer",
    "vkBindBufferMemory",
    "vkBindBufferMemory2",
    "vkBindBufferMemory2KHR",
    "vkBindImageMemory",
    "vkBindImageMemory2",
    "vkBindImageMemory2KHR",
    "vkCmdBeginQuery",
    "vkCmdBeginRenderPass",
    "vkCmdBeginRenderPass2",
    "vkCmdBeginRenderPass2KHR",
    "vkCmdBeginRendering",
    "vkCmdBeginRenderingKHR",
    "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT",
    "vkCmdBindDescriptorSets",
    "vkCmdBindDescriptorSets2",
    "vkCmdBindDescriptorSets2KHR",
    "vkCmdBindIndexBuffer",
    "vkCmdBindIndexBuffer2",
    "vkCmdBindIndexBuffer2KHR",
    "vkCmdBindPipeline",
    "vkCmdBindShadersEXT",
    "vkCmdBindVertexBuffers",
    "vkCmdBindVertexBuffers2",
    "vkCmdBindVertexBuffers2EXT",
    "vkCmdBlitImage",
    "vkCmdBlitImage2",
    "vkCmdBlitImage2KHR",
    "vkCmdClearAttachments",
    "vkCmdClearColorImage",
    "vkCmdClearDepthStencilImage",
    "vkCmdCopyBuffer",
    "vkCmdCopyBuffer2",
    "vkCmdCopyBuffer2KHR",
    "vkCmdCopyBufferToImage",
    "vkCmdCopyBufferToImage2",
    "vkCmdCopyBufferToImage2KHR",
    "vkCmdCopyImage",
    "vkCmdCopyImage2",
    "vkCmdCopyImage2KHR",
    "vkCmdCopyImageToBuffer",
    "vkCmdCopyImageToBuffer2",
    "vkCmdCopyImageToBuffer2KHR",
    "vkCmdCopyQueryPoolResults",
    "vkCmdDispatch",
    "vkCmdDispatchBase",
    "vkCmdDispatchBaseKHR",
    "vkCmdDispatchIndirect",
    "vkCmdDraw",
    "vkCmdDrawIndexed",
    "vkCmdDrawIndexedIndirect",
    "vkCmdDrawIndexedIndirectCount",
    "vkCmdDrawIndexedIndirectCountAMD",
    "vkCmdDrawIndexedIndirectCountKHR",
    "vkCmdDrawIndirect",
    "vkCmdDrawIndirectCount",
    "vkCmdDrawIndirectCountAMD",
    "vkCmdDrawIndirectCountKHR",
    "vkCmdEndQuery",
    "vkCmdEndRenderPass",
    "vkCmdEndRenderPass2",
    "vkCmdEndRenderPass2KHR",
    "vkCmdEndRendering",
    "vkCmdEndRenderingKHR",
    "vkCmdExecuteCommands",
    "vkCmdFillBuffer",
    "vkCmdNextSubpass",
    "vkCmdNextSubpass2",
    "vkCmdNextSubpass2KHR",
    "vkCmdPipelineBarrier",
    "vkCmdPipelineBarrier2",
    "vkCmdPipelineBarrier2KHR",
    "vkCmdPushConstants",
    "vkCmdPushConstants2",
    "vkCmdPushConstants2KHR",
    "vkCmdPushDescriptorSet",
    "vkCmdPushDescriptorSet2",
    "vkCmdPushDescriptorSet2KHR",
    "vkCmdPushDescriptorSetKHR",
    "vkCmdPushDescriptorSetWithTemplate",
    "vkCmdPushDescriptorSetWithTemplate2",
    "vkCmdPushDescriptorSetWithTemplate2KHR",
    "vkCmdPushDescriptorSetWithTemplateKHR",
    "vkCmdResetEvent",
    "vkCmdResetEvent2",
    "vkCmdResetEvent2KHR",
    "vkCmdResetQueryPool",
    "vkCmdResolveImage",
    "vkCmdResolveImage2",
    "vkCmdResolveImage2KHR",
    "vkCmdSetAlphaToCoverageEnableEXT",
    "vkCmdSetAlphaToOneEnableEXT",
    "vkCmdSetBlendConstants",
    "vkCmdSetColorBlendAdvancedEXT",
    "vkCmdSetColorBlendEnableEXT",
    "vkCmdSetColorBlendEquationEXT",
    "vkCmdSetColorWriteMaskEXT",
    "vkCmdSetConservativeRasterizationModeEXT",
    "vkCmdSetCoverageModulationModeNV",
    "vkCmdSetCoverageModulationTableEnableNV",
    "vkCmdSetCoverageModulationTableNV",
    "vkCmdSetCoverageReductionModeNV",
    "vkCmdSetCoverageToColorEnableNV",
    "vkCmdSetCoverageToColorLocationNV",
    "vkCmdSetCullMode",
    "vkCmdSetCullModeEXT",
    "vkCmdSetDepthBias",
    "vkCmdSetDepthBiasEnable",
    "vkCmdSetDepthBiasEnableEXT",
    "vkCmdSetDepthBounds",
    "vkCmdSetDepthBoundsTestEnable",
    "vkCmdSetDepthBoundsTestEnableEXT",
    "vkCmdSetDepthClampEnableEXT",
    "vkCmdSetDepthClampRangeEXT",
    "vkCmdSetDepthClipEnableEXT",
    "vkCmdSetDepthClipNegativeOneToOneEXT",
    "vkCmdSetDepthCompareOp",
    "vkCmdSetDepthCompareOpEXT",
    "vkCmdSetDepthTestEnable",
    "vkCmdSetDepthTestEnableEXT",
    "vkCmdSetDepthWriteEnable",
    "vkCmdSetDepthWriteEnableEXT",
    "vkCmdSetDescriptorBufferOffsets2EXT",
    "vkCmdSetDeviceMask",
    "vkCmdSetDeviceMaskKHR",
    "vkCmdSetEvent",
    "vkCmdSetEvent2",
    "vkCmdSetEvent2KHR",
    "vkCmdSetExtraPrimitiveOverestimationSizeEXT",
    "vkCmdSetFrontFace",
    "vkCmdSetFrontFaceEXT",
    "vkCmdSetLineRasterizationModeEXT",
    "vkCmdSetLineStipple",
    "vkCmdSetLineStippleEXT",
    "vkCmdSetLineStippleEnableEXT",
    "vkCmdSetLineStippleKHR",
    "vkCmdSetLineWidth",
    "vkCmdSetLogicOpEXT",
    "vkCmdSetLogicOpEnableEXT",
    "vkCmdSetPatchControlPointsEXT",
    "vkCmdSetPolygonModeEXT",
    "vkCmdSetPrimitiveRestartEnable",
    "vkCmdSetPrimitiveRestartEnableEXT",
    "vkCmdSetPrimitiveTopology",
    "vkCmdSetPrimitiveTopologyEXT",
    "vkCmdSetProvokingVertexModeEXT",
    "vkCmdSetRasterizationSamplesEXT",
    "vkCmdSetRasterizationStreamEXT",
    "vkCmdSetRasterizerDiscardEnable",
    "vkCmdSetRasterizerDiscardEnableEXT",
    "vkCmdSetRenderingAttachmentLocations",
    "vkCmdSetRenderingAttachmentLocationsKHR",
    "vkCmdSetRenderingInputAttachmentIndices",
    "vkCmdSetRenderingInputAttachmentIndicesKHR",
    "vkCmdSetRepresentativeFragmentTestEnableNV",
    "vkCmdSetSampleLocationsEnableEXT",
    "vkCmdSetSampleMaskEXT",
    "vkCmdSetScissor",
    "vkCmdSetScissorWithCount",
    "vkCmdSetScissorWithCountEXT",
    "vkCmdSetShadingRateImageEnableNV",
    "vkCmdSetStencilCompareMask",
    "vkCmdSetStencilOp",
    "vkCmdSetStencilOpEXT",
    "vkCmdSetStencilReference",
    "vkCmdSetStencilTestEnable",
    "vkCmdSetStencilTestEnableEXT",
    "vkCmdSetStencilWriteMask",
    "vkCmdSetTessellationDomainOriginEXT",
    "vkCmdSetVertexInputEXT",
    "vkCmdSetViewport",
    "vkCmdSetViewportSwizzleNV",
    "vkCmdSetViewportWScalingEnableNV",
    "vkCmdSetViewportWithCount",
    "vkCmdSetViewportWithCountEXT",
    "vkCmdUpdateBuffer",
    "vkCmdWaitEvents",
    "vkCmdWaitEvents2",
    "vkCmdWaitEvents2KHR",
    "vkCmdWriteTimestamp",
    "vkCmdWriteTimestamp2",
    "vkCmdWriteTimestamp2KHR",
    "vkCopyImageToImage",
    "vkCopyImageToImageEXT",
    "vkCopyImageToMemory",
    "vkCopyImageToMemoryEXT",
    "vkCopyMemoryToImage",
    "vkCopyMemoryToImageEXT",
    "vkCreateBuffer",
    "vkCreateBufferView",
    "vkCreateCommandPool",
    "vkCreateComputePipelines",
    "vkCreateDescriptorPool",
    "vkCreateDescriptorSetLayout",
    "vkCreateDescriptorUpdateTemplate",
    "vkCreateDescriptorUpdateTemplateKHR",
    "vkCreateEvent",
    "vkCreateFence",
    "vkCreateFramebuffer",
    "vkCreateGraphicsPipelines",
    "vkCreateImage",
    "vkCreateImageView",
    "vkCreatePipelineCache",
    "vkCreatePipelineLayout",
    "vkCreatePrivateDataSlot",
    "vkCreatePrivateDataSlotEXT",
    "vkCreateQueryPool",
    "vkCreateRenderPass",
    "vkCreateRenderPass2",
    "vkCreateRenderPass2KHR",
    "vkCreateSampler",
    "vkCreateSamplerYcbcrConversion",
    "vkCreateSamplerYcbcrConversionKHR",
    "vkCreateSemaphore",
    "vkCreateShaderModule",
    "vkCreateShadersEXT",
    "vkDestroyBuffer",
    "vkDestroyBufferView",
    "vkDestroyCommandPool",
    "vkDestroyDescriptorPool",
    "vkDestroyDescriptorSetLayout",
    "vkDestroyDescriptorUpdateTemplate",
    "vkDestroyDescriptorUpdateTemplateKHR",
    "vkDestroyDevice",
    "vkDestroyEvent",
    "vkDestroyFence",
    "vkDestroyFramebuffer",
    "vkDestroyImage",
    "vkDestroyImageView",
    "vkDestroyPipeline",
    "vkDestroyPipelineCache",
    "vkDestroyPipelineLayout",
    "vkDestroyPrivateDataSlot",
    "vkDestroyPrivateDataSlotEXT",
    "vkDestroyQueryPool",
    "vkDestroyRenderPass",
    "vkDestroySampler",
    "vkDestroySamplerYcbcrConversion",
    "vkDestroySamplerYcbcrConversionKHR",
    "vkDestroySemaphore",
    "vkDestroyShaderEXT",
    "vkDestroyShaderModule",
    "vkDeviceWaitIdle",
    "vkEndCommandBuffer",
    "vkFlushMappedMemoryRanges",
    "vkFreeCommandBuffers",
    "vkFreeDescriptorSets",
    "vkFreeMemory",
    "vkGetBufferDeviceAddress",
    "vkGetBufferDeviceAddressEXT",
    "vkGetBufferDeviceAddressKHR",
    "vkGetBufferMemoryRequirements",
    "vkGetBufferMemoryRequirements2",
    "vkGetBufferMemoryRequirements2KHR",
    "vkGetBufferOpaqueCaptureAddress",
    "vkGetBufferOpaqueCaptureAddressKHR",
    "vkGetDescriptorSetLayoutSupport",
    "vkGetDescriptorSetLayoutSupportKHR",
    "vkGetDeviceBufferMemoryRequirements",
    "vkGetDeviceBufferMemoryRequirementsKHR",
    "vkGetDeviceGroupPeerMemoryFeatures",
    "vkGetDeviceGroupPeerMemoryFeaturesKHR",
    "vkGetDeviceGroupPresentCapabilitiesKHR",
    "vkGetDeviceGroupSurfacePresentModesKHR",
    "vkGetDeviceImageMemoryRequirements",
    "vkGetDeviceImageMemoryRequirementsKHR",
    "vkGetDeviceImageSparseMemoryRequirements",
    "vkGetDeviceImageSparseMemoryRequirementsKHR",
    "vkGetDeviceImageSubresourceLayout",
    "vkGetDeviceImageSubresourceLayoutKHR",
    "vkGetDeviceMemoryCommitment",
    "vkGetDeviceMemoryOpaqueCaptureAddress",
    "vkGetDeviceMemoryOpaqueCaptureAddressKHR",
    "vkGetDeviceProcAddr",
    "vkGetDeviceQueue",
    "vkGetDeviceQueue2",
    "vkGetEventStatus",
    "vkGetFenceStatus",
    "vkGetImageMemoryRequirements",
    "vkGetImageMemoryRequirements2",
    "vkGetImageMemoryRequirements2KHR",
    "vkGetImageSparseMemoryRequirements",
    "vkGetImageSparseMemoryRequirements2",
    "vkGetImageSparseMemoryRequirements2KHR",
    "vkGetImageSubresourceLayout",
    "vkGetImageSubresourceLayout2",
    "vkGetImageSubresourceLayout2EXT",
    "vkGetImageSubresourceLayout2KHR",
    "vkGetPipelineCacheData",
    "vkGetPrivateData",
    "vkGetPrivateDataEXT",
    "vkGetQueryPoolResults",
    "vkGetRenderAreaGranularity",
    "vkGetRenderingAreaGranularity",
    "vkGetRenderingAreaGranularityKHR",
    "vkGetSemaphoreCounterValue",
    "vkGetSemaphoreCounterValueKHR",
    "vkGetShaderBinaryDataEXT",
    "vkInvalidateMappedMemoryRanges",
    "vkMapMemory",
    "vkMapMemory2",
    "vkMapMemory2KHR",
    "vkMergePipelineCaches",
    "vkQueueBindSparse",
    "vkQueueSubmit",
    "vkQueueSubmit2",
    "vkQueueSubmit2KHR",
    "vkQueueWaitIdle",
    "vkResetCommandBuffer",
    "vkResetCommandPool",
    "vkResetDescriptorPool",
    "vkResetEvent",
    "vkResetFences",
    "vkResetQueryPool",
    "vkResetQueryPoolEXT",
    "vkSetEvent",
    "vkSetPrivateData",
    "vkSetPrivateDataEXT",
    "vkSignalSemaphore",
    "vkSignalSemaphoreKHR",
    "vkTransitionImageLayout",
    "vkTransitionImageLayoutEXT",
    "vkTrimCommandPool",
    "vkTrimCommandPoolKHR",
    "vkUnmapMemory",
    "vkUnmapMemory2",
    "vkUnmapMemory2KHR",
    "vkUpdateDescriptorSetWithTemplate",
    "vkUpdateDescriptorSetWithTemplateKHR",
    "vkUpdateDescriptorSets",
    "vkWaitForFences",
    "vkWaitSemaphores",
    "vkWaitSemaphoresKHR",
};

static int glad_vulkan_is_device_function(const char *name) {
    /* Exists as a workaround for:
     * https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/issues/2323
     *
     * `vkGetDeviceProcAddr` does not return NULL for non-device functions.
     */
    int i;
    int length = sizeof(DEVICE_FUNCTIONS) / sizeof(DEVICE_FUNCTIONS[0]);

    for (i=0; i < length; ++i) {
        if (strcmp(DEVICE_FUNCTIONS[i], name) == 0) {
            return 1;
        }
    }

    return 0;
}

struct _glad_vulkan_userptr {
    void *vk_handle;
    VkInstance vk_instance;
    VkDevice vk_device;
    PFN_vkGetInstanceProcAddr get_instance_proc_addr;
    PFN_vkGetDeviceProcAddr get_device_proc_addr;
};

static GLADapiproc glad_vulkan_get_proc(void *vuserptr, const char *name) {
    struct _glad_vulkan_userptr userptr = *(struct _glad_vulkan_userptr*) vuserptr;
    PFN_vkVoidFunction result = NULL;

    if (userptr.vk_device != NULL && glad_vulkan_is_device_function(name)) {
        result = userptr.get_device_proc_addr(userptr.vk_device, name);
    }

    if (result == NULL && userptr.vk_instance != NULL) {
        result = userptr.get_instance_proc_addr(userptr.vk_instance, name);
    }

    if(result == NULL) {
        result = (PFN_vkVoidFunction) glad_dlsym_handle(userptr.vk_handle, name);
    }

    return (GLADapiproc) result;
}


static void* _glad_Vulkan_loader_handle = NULL;

static void* glad_vulkan_dlopen_handle(void) {
    static const char *NAMES[] = {
#if GLAD_PLATFORM_APPLE
        "libvulkan.1.dylib",
#elif GLAD_PLATFORM_WIN32
        "vulkan-1.dll",
        "vulkan.dll",
#else
        "libvulkan.so.1",
        "libvulkan.so",
#endif
    };

    if (_glad_Vulkan_loader_handle == NULL) {
        _glad_Vulkan_loader_handle = glad_get_dlopen_handle(NAMES, sizeof(NAMES) / sizeof(NAMES[0]));
    }

    return _glad_Vulkan_loader_handle;
}

static struct _glad_vulkan_userptr glad_vulkan_build_userptr(void *handle, VkInstance instance, VkDevice device) {
    struct _glad_vulkan_userptr userptr;
    userptr.vk_handle = handle;
    userptr.vk_instance = instance;
    userptr.vk_device = device;
    userptr.get_instance_proc_addr = (PFN_vkGetInstanceProcAddr) glad_dlsym_handle(handle, "vkGetInstanceProcAddr");
    userptr.get_device_proc_addr = (PFN_vkGetDeviceProcAddr) glad_dlsym_handle(handle, "vkGetDeviceProcAddr");
    return userptr;
}

int gladLoaderLoadVulkan( VkInstance instance, VkPhysicalDevice physical_device, VkDevice device) {
    int version = 0;
    void *handle = NULL;
    int did_load = 0;
    struct _glad_vulkan_userptr userptr;

    did_load = _glad_Vulkan_loader_handle == NULL;
    handle = glad_vulkan_dlopen_handle();
    if (handle != NULL) {
        userptr = glad_vulkan_build_userptr(handle, instance, device);

        if (userptr.get_instance_proc_addr != NULL && userptr.get_device_proc_addr != NULL) {
            version = gladLoadVulkanUserPtr( physical_device, glad_vulkan_get_proc, &userptr);
        }

        if (!version && did_load) {
            gladLoaderUnloadVulkan();
        }
    }

    return version;
}



void gladLoaderUnloadVulkan(void) {
    if (_glad_Vulkan_loader_handle != NULL) {
        glad_close_dlopen_handle(_glad_Vulkan_loader_handle);
        _glad_Vulkan_loader_handle = NULL;
    }
}

#endif /* GLAD_VULKAN */

#ifdef __cplusplus
}
#endif
