#include <gtest/gtest.h>
#include "../src/npc.h"
#include <memory>
#include <vector>
#include <filesystem>
#include "../src/logger/ILogger.h"
#include "../src/backup.h"
#include "../src/logger/file_logger.h"

void RemoveIfExists(const std::string& filename) {
    if (std::filesystem::exists(filename)) std::filesystem::remove(filename);
}

std::string read(std::istream &file) {
    std::string buff;
    std::string result;

    while (std::getline(file, buff))
        result += buff + '\n';

    return result;
}

TEST(BackupLoaderTests, ShouldDumpAndLoadData) {
    std::vector<std::shared_ptr<Logger::ILogger>> logger {std::make_shared<Logger::ConsoleLogger>()};

    set_t array;

    std::cout << "Generating ..." << std::endl;
    array.insert(
            factory(OrcType,
                    1,
                    1,
                    "name",
                    1,
                    true
                    ));
    array.insert(
            factory(DruidType,
                    2,
                    3,
                    "name1",
                    1,
                    true
    ));
    array.insert(
            factory(SlaveTraderType,
                    3,
                    3,
                    "name2",
                    1,
                    true
    ));

    std::string backupFileName = "backup.text";

    Backuper::save(array, backupFileName);
    auto state = Backuper::load(backupFileName);

    EXPECT_EQ(state.size(), array.size());

    EXPECT_EQ(state.size(), array.size());

    auto beg = state.begin();
    auto beg1 = array.begin();

    while (beg != state.end()) {
        EXPECT_EQ(**beg, **beg1);
        beg++; beg1++;
    }

    RemoveIfExists(backupFileName);
}

TEST(ConsoleLoggerTests, ShouldLogCorrectly){
    std::ostringstream oss;
    auto logger = Logger::ConsoleLogger(oss, "name");
    logger.log("qwe");
    logger.log("qwe");
    EXPECT_EQ(oss.str(), "qwe\nqwe\n");
}

TEST(FileLoggerTests, ShouldLogCorrectly){
    {
        auto logger = Logger::FileLogger("file.txt", "name");
        logger.log("qwe");
        logger.log("qwe");
    }

    std::ifstream file("file.txt");

    EXPECT_TRUE(file.good());

    std::string result = read(file);
    file.close();
    RemoveIfExists("file.txt");

    EXPECT_EQ(result, "qwe\nqwe\n");
}

TEST(VisitorTests, ShouldVisitCorrectly) {
    std::ostringstream oss;
    std::shared_ptr<Logger::ILogger> logger = std::make_shared<Logger::ConsoleLogger>(oss, "name");

    auto st = factory(SlaveTraderType,3,3,"name2", 1, true);
    auto druid = factory(DruidType,3,3,"name1", 1, true);

    st->subscribe(logger);
    druid->subscribe(logger);

    st->accept(druid);
    druid->accept(st);
    EXPECT_EQ(oss.str(), "name1 of type Druid got killed by name2 of type SlaveTrader\n");
}

TEST(VisitorTests, ShouldNotKillIfNotAlive) {
    std::ostringstream oss;
    std::shared_ptr<Logger::ILogger> logger = std::make_shared<Logger::ConsoleLogger>(oss, "name");

    auto st = factory(SlaveTraderType,3,3,"name2", 1, true);
    auto druid = factory(DruidType,3,3,"name1", 1, false);

    st->subscribe(logger);
    druid->subscribe(logger);

    st->accept(druid);
    druid->accept(st);
    EXPECT_EQ(oss.str(), "");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
