#include <gtest/gtest.h>
#include "../src/npc.h"
#include "../src/orc.h"
#include "../src/druid.h"
#include "../src/slave_trader.h"
#include <memory>
#include <vector>
#include <filesystem>
#include "../src/logger/ILogger.h"
#include "../src/backup.h"

void RemoveIfExists(const std::string& filename) {
    if (std::filesystem::exists(filename)) std::filesystem::remove(filename);
}

TEST(BackupLoaderTests, ShouldDumpAndLoadData) {
    std::vector<std::shared_ptr<Logger::ILogger>> logger {std::make_shared<Logger::ConsoleLogger>()};

    set_t array;

    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 100; ++i)
    array.insert(
            factory(OrcType,
                    1,
                    1,
                    "name",
                    true
                    ));
    array.insert(
            factory(DruidType,
                    2,
                    3,
                    "name1",
                    true
    ));
    array.insert(
            factory(SlaveTraderType,
                    3,
                    3,
                    "name2",
                    true
    ));

    std::string backupFileName = "backup.text";

    Backuper::save(array, backupFileName);
    auto state = Backuper::load(backupFileName);

    EXPECT_EQ(state.size(), array.size());

    for (auto idx = 0; idx < array.size(); ++idx) {
        EXPECT_TRUE(*state[idx] == *array[idx]);
    }

    RemoveIfExists(backupFileName);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}