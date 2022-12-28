#include "LocationMapStateCache.h"

void LocationMapCache::add_state(uint64_t tick_id, std::shared_ptr<LocationMapShortState> state) {
    semaphore.acquire();
    if (!cached_states.contains(tick_id)) {
        cached_states[tick_id] = state;
        item_count++;
    }
    semaphore.release();
}

std::shared_ptr<std::string> LocationMapCache::get_map(uint64_t tick_id) {
    std::shared_ptr<std::string> res = std::make_shared<std::string>("");

    semaphore.acquire();
    if (!cached_output_full.contains(tick_id)) {
        if (!cached_states.contains(tick_id)) {
            // No cached JSON + no cached state
            // Just return the latest map
            res = _get_latest_map();
            goto release;
        }
    }
    release:
    semaphore.release();

    return res;
}

std::shared_ptr<std::string> LocationMapCache::_get_latest_map() {
    std::shared_ptr<std::string> res = std::make_shared<std::string>("");

    if (cached_output_full.size()) {
        res = cached_output_full.rbegin()->second;
    }

    return res;
}

std::shared_ptr<std::string> LocationMapCache::get_latest_map() {
    std::shared_ptr<std::string> res = std::make_shared<std::string>("");

    semaphore.acquire();
    res = _get_latest_map();
    semaphore.release();

    return res;
}

std::shared_ptr<std::string> LocationMapCache::get_update(uint64_t base_tick_id) {
    std::shared_ptr<std::string> res = std::make_shared<std::string>("");

    semaphore.acquire();

    if (!cached_output_diff.contains(base_tick_id)) {
        if (!cached_states.contains(base_tick_id)) {
            // No diff in cache and
        }
    }

    if (cached_states.size()) {
        uint64_t newest_tick_id = cached_states.rbegin()->first;
    }
    semaphore.release();

    return res;
}

void LocationMapCache::set_min_items(size_t value) {
    min_items = value;
}

void LocationMapCache::set_max_items(size_t value) {
    max_items = value;
}
