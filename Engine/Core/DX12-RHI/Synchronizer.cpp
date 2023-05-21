#include "Synchronizer.h"

void Machi::GraphicsSyncManager::wait_gpu(CommandQueue& queue, MUINT frame_index)
{
    // Schedule a Signal command in the queue.
    ThrowIfFailed(queue->Signal(m_fence.Get(), m_fence_value[frame_index]));

    // Wait until the fence has been processed.
    ThrowIfFailed(m_fence->SetEventOnCompletion(m_fence_value[frame_index], m_fence_event));
    WaitForSingleObjectEx(m_fence_event, INFINITE, FALSE);

    // Increment the fence value for the current frame.
    m_fenceValues[frame_index]++;
}


void Machi::GraphicsSyncManager::next_frame(CommandQueue& queue, SwapChain& swapchain) {

    // Schedule a Signal command in the queue.
    const UINT64 cur_fence_value = m_fence_value[frame_index];
    std::cout << m_fence->GetCompletedValue() << std::endl;
    ThrowIfFailed(m_commandQueue->Signal(m_fence.Get(), cur_fence_value));
    std::cout << m_fence->GetCompletedValue() << std::endl;

    // Update the frame index.
    frame_index = swapchain->GetCurrentBackBufferIndex();

    // If the next frame is not ready to be rendered yet, wait until it is ready.
    if (m_fence->GetCompletedValue() < m_fence_value[frame_index])
    {
        ThrowIfFailed(m_fence->SetEventOnCompletion(m_fence_value[frame_index], m_fence_event));
        WaitForSingleObjectEx(m_fence_event, INFINITE, FALSE);
    }

    // Set the fence value for the next frame.
    m_fence_value[frame_index] = cur_fence_value + 1;
}
