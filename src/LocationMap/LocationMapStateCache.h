#include <map>
#include <memory>
#include <semaphore>

#include "LocationMapStateShort.h"

class LocationMapCache {
public:
    /**
     * @brief Add a map version to the cache
     */
    void add_state(uint64_t tick_id, std::shared_ptr<LocationMapShortState> state);

    /**
     * @brief Get specific version of the map
     */
    std::shared_ptr<std::string> get_map(uint64_t tick_id);

    /**
     * @brief Get the last version of the map
     */
    std::shared_ptr<std::string> get_latest_map();

    /**
     * @brief Get difference between the last map version and one available to the user
     *
     * If the base version is not available to the user, the full map is transferred.
     *
     * @param base_tick_id Tick ID of the map the user has.
     */
    std::shared_ptr<std::string> get_update(uint64_t base_tick_id);

    /**
     * @brief Set minimum number of states in the cache
     *
     * The cache clearing is stopped when this number of items is left in the cache.
     */
    void set_min_items(size_t value);

    /**
     * @brief Set maximum number of items in the cache
     *
     * If there are more items in the cache, cache clearing is triggered
     */
    void set_max_items(size_t value);
private:
    // key = tick ID
    std::map<uint64_t, std::shared_ptr<LocationMapShortState>> cached_states;
    std::map<uint64_t, std::shared_ptr<std::string>> cached_output_full;
    // first key = base tick ID, second key = new tick ID
    std::map<uint64_t, std::map<uint64_t, std::shared_ptr<std::string>>> cached_output_diff;

    std::binary_semaphore semaphore{1};

    size_t min_items = 100;
    size_t max_items = 1000;

    size_t item_count = 0;

    /**
     * @brief Get the latest map without locking
     */
    std::shared_ptr<std::string> _get_latest_map();
};
