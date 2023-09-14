#include "Synchronizer.h"
#include "dxhelper.h"
#include <iostream>
#include <Graphics/graphics_defined.h>
using namespace Machi::NativeGraphics;


bool GraphicsSyncManager::create(std::shared_ptr<Device> device, MUINT64 fence_size) {
    m_fence_size = fence_size;

    ThrowIfFailed(device->create_fence(0, FenceFlags::MACHI_FENCE_FLAG_NONE, m_fence));
    std::make_unique<UINT64[]>(m_fence_size);
    for (int i = 0; i < m_fence_size; i++)
        m_fence_value[i] = 1;
    m_fence_size = fence_size;
    0, FenceFlags::MACHI_FENCE_FLAG_NONE, 
    // Create an event handle to use for frame synchronization.
    m_fence_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (m_fence_event == nullptr)
    {
        ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
    }


    return true;
}

void GraphicsSyncManager::wait_gpu(CommandQueue& queue, MUINT frame_index)
{
    // Schedule a Signal command in the queue.
    ThrowIfFailed(queue->Signal(m_fence.Get(), m_fence_value[frame_index]));

    // Wait until the fence has been processed.
    ThrowIfFailed(m_fence->SetEventOnCompletion(m_fence_value[frame_index], m_fence_event));
    WaitForSingleObjectEx(m_fence_event, INFINITE, FALSE);

    // Increment the fence value for the current frame.
    m_fence_value[frame_index]++;
}


void GraphicsSyncManager::next_frame(CommandQueue& queue, SwapChain& swapchain) {

    // Schedule a Signal command in the queue.
    const UINT64 cur_fence_value = m_fence_value[m_frame_index];
    std::cout << m_fence->GetCompletedValue() << std::endl;
    ThrowIfFailed(queue->Signal(m_fence.Get(), cur_fence_value));
    std::cout << m_fence->GetCompletedValue() << std::endl;

    // Update the frame index.
    m_frame_index = swapchain->GetCurrentBackBufferIndex();

    // If the next frame is not ready to be rendered yet, wait until it is ready.
    if (m_fence->GetCompletedValue() < m_fence_value[m_frame_index])
    {
        ThrowIfFailed(m_fence->SetEventOnCompletion(m_fence_value[m_frame_index], m_fence_event));
        WaitForSingleObjectEx(m_fence_event, INFINITE, FALSE);
    }

    // Set the fence value for the next frame.
    m_fence_value[m_frame_index] = cur_fence_value + 1;
}
