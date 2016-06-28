#include <atomic>

#include <realm/disable_sync_to_disk.hpp>

using namespace realm;

namespace {

std::atomic<bool> g_disable_sync_to_disk(false);

} // anonymous namespace

// LCOV_EXCL_START We will sync to disc during coverage run
void realm::disable_sync_to_disk()
{
    g_disable_sync_to_disk = true;
}
// LCOV_EXCL_STOP

bool realm::get_disable_sync_to_disk() noexcept
{
    return g_disable_sync_to_disk;
}
