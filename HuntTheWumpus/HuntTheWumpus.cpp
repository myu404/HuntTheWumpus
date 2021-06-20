/*
* Author: Michael Yu
* C++ Programming, Spring 2021
* Hunt The Wumpus: Assignment 05
* 6/20/2021
*/

#include "Context.h"
#include "Dungeon.h"
#include "RandomProvider.h"
#include "GameStateObservation.h"
#include "UserNotification.h"

#include "CustomAssert.h"

#include <iostream>
#include <random>
#include <string>
#include <stdexcept>

class RandomCave final : public HuntTheWumpus::IRandomProvider
{
public:

    RandomCave() = default;
    ~RandomCave() override = default;

    int MakeRandomCave() override
    {
        return m_distributionCave(m_generator);
    }

    int MakeRandomTunnel() override
    {
        return m_distributionTunnel(m_generator);
    }

    float MakeRandomNumber() override
    {
        return m_distributionRandom(m_generator);
    }

    RandomCave(const RandomCave&) = default;
    RandomCave(RandomCave&&) = default;
    RandomCave& operator=(const RandomCave&) = default;
    RandomCave& operator=(RandomCave&&) = default;

private:

    std::mt19937 m_generator = std::mt19937(static_cast<unsigned int>(time(nullptr)));  // NOLINT(cert-msc51-cpp)
    std::uniform_int_distribution<int> m_distributionCave = std::uniform_int_distribution<int>(1, 20);
    std::uniform_int_distribution<int> m_distributionTunnel = std::uniform_int_distribution<int>(0, 2);
    std::uniform_real_distribution<float> m_distributionRandom = std::uniform_real_distribution<float>(0.0f, 1.0f);
};

HuntTheWumpus::UserNotification MakeUserNotifications()
{
    HuntTheWumpus::UserNotification notify;

    notify.AddCallback(HuntTheWumpus::UserNotification::Notification::ObserveWumpus, []() {
        std::cout << "You smell a horrid stench..." << std::endl;
    });

    notify.AddCallback(HuntTheWumpus::UserNotification::Notification::ObservePit, []() {
        std::cout << "You feel a draft..." << std::endl;
    });

    notify.AddCallback(HuntTheWumpus::UserNotification::Notification::ObserveBat, []() {
        std::cout << "Bats nearby..." << std::endl;
    });

    notify.AddCallback(HuntTheWumpus::UserNotification::Notification::BatTriggered, []() {
        std::cout << "Zap -- Super Bat Snatch! Elsewhereville for you!" << std::endl;
    });

    notify.AddCallback(HuntTheWumpus::UserNotification::Notification::PitTriggered, []() {
        std::cout << "YYYIIIIEFEE . . . Fell in pit." << std::endl;
    });

    notify.AddCallback(HuntTheWumpus::UserNotification::Notification::WumpusAwoken, []() {
        std::cout << "...oops! Bumped a Wumpus!" << std::endl;
    });

    notify.AddCallback(HuntTheWumpus::UserNotification::Notification::WumpusShot, []() {
        std::cout << "Aha! You got the Wumpus!" << std::endl;
    });

    notify.AddCallback(HuntTheWumpus::UserNotification::Notification::HunterEaten, []() {
        std::cout << "Tsk tsk tsk -- Wumpus got you!" << std::endl;
    });

    notify.AddCallback(HuntTheWumpus::UserNotification::Notification::HunterShot, []() {
        std::cout << "Ouch! Arrow got you!" << std::endl;
    });

    notify.AddCallback(HuntTheWumpus::UserNotification::Notification::CaveEntered, [](const int caveId) {
        std::cout << "You've entered cave " << caveId << std::endl;
    });

    notify.AddCallback(HuntTheWumpus::UserNotification::Notification::NeighboringCaves, [](const std::vector<int>& neighbors) {
        std::cout << "Tunnels lead to: ";

        for (auto caveId : neighbors)
        {
            std::cout << " " << caveId;
        }

        std::cout << std::endl;
    });

    notify.AddCallback(HuntTheWumpus::UserNotification::Notification::ObserveMiss, []() {
        std::cout << "Missed!" << std::endl;
    });

    notify.AddCallback(HuntTheWumpus::UserNotification::Notification::ObserveOutOfArrows, []() {
        std::cout << "You do not have any more arrows!" << std::endl;
    });

    notify.AddCallback(HuntTheWumpus::UserNotification::Notification::ReportIllegalMove, [](const int destinationId) {
        std::cout << "You can't get to " << destinationId << " from here." << std::endl;
    });

    return notify;
}

class GameChange final : public HuntTheWumpus::IGameStateChange
{
public:
    GameChange() = default;
    ~GameChange() override = default;

    void GameOver(const bool won) override
    {
        std::cout << "Game over: you " << (won ? "won" : "lost") << "." << std::endl;
        m_playing = false;
    }

    bool IsPlaying() const override { return m_playing; }

    GameChange(const GameChange&) = default;
    GameChange(GameChange&&) = default;
    GameChange& operator=(const GameChange&) = default;
    GameChange& operator=(GameChange&&) = default;

private:
    bool m_playing = true;
};

std::vector<std::string> SplitString(const std::string& text, const std::string& delims)
{
    std::vector<std::string> tokens;
    std::size_t start = text.find_first_not_of(delims), end;

    while ((end = text.find_first_of(delims, start)) != std::string::npos)
    {
        tokens.push_back(text.substr(start, end - start));
        start = text.find_first_not_of(delims, end);
    }

    if (start != std::string::npos)
    {
        tokens.push_back(text.substr(start));
    }

    return tokens;
}

/*
class InputError : public std::exception
{
public:
    InputError()
        : std::exception("ERROR: Invalid input.\nEnter \"m\", \"M\", \"move\", or \"MOVE\" for move command.\nEnter \"s\", \"S\", \"shoot\", or \"SHOOT\" for shoot command.\n"
        "Move and shoot command must be followed be followed by destination cave id (move) or list of cave ids (shoot).\n"
        "Enter \"q\", \"quit\", \"e\", \"exit\", or \"x\" to quit program.")
    {
    }
};
*/

void PrintWelcomeText()
{
    std::string instructions =
        "Welcome to \"Hunt the Wumpus\".\n"
        "The wumpus lives in a dungeon of 20 caves.Each cave has 3 tunnels to other caves.\n"
        "(Look at a dodecahedron to see how this works.If you print \"don\'t know what a dodecahedron is, ask someone.)\n"
        "\nHazards:\n"
        "\tBottomless pits - Two caves have bottomless pits in them.If you go there, you fall into the pit(& lose)!\n"
        "\tSuper bats - Two caves have super bats.If you go there, a bat grabs you and takes you to some other room at random(which may be troublesome).\n"
        "Wumpus:\n"
        "\tThe wumpus is not bothered by hazards. (He has sucker feet and is too big for a\n"
        "bat to lift.) Usually he is asleep.Two things wake him up : your shooting an\n"
        "arrow, or your entering his room.If the wumpus wakes, he moves(75 % of the time)\n"
        "one room or stays still(25 % of the time). After that, if he is where you are, he eats you upand you lose!\n"
        "\nEach turn you may move or shoot a crooked arrow.\n"
        "Moving : You can move one cave(through one tunnel).\n"
        "Arrows : You have 5 arrows.You lose when you run out.Each arrow can go from 1 to 5 caves.You aim by telling the caves to which you want the arrow to go.\n"
        "If the arrow can\'t go that way (if no tunnel) it moves at random to a neighboring cave.\n"
        "\tIf the arrow hits the wumpus, you win.\n"
        "\tIf the arrow hits you, you lose.\n"
        "Warnings :\n"
        "\tWhen you are one room away from a wumpus or hazard, the computer says:\n"
        "\tWumpus: \"I smell a wumpus!\"\n"
        "\tBat : \"Bats nearby!\"\n"
        "\tPit : \"I feel a draft!\"\n";

    std::cout << instructions << std::endl;
}

const std::vector<std::string> validCommands = { "m", "M", "move", "MOVE", "s", "S", "shoot", "SHOOT", "q", "quit", "e", "exit", "x" };

int main()
{
    PrintWelcomeText();
    RandomCave sourceOfRandom;
    GameChange change;

    auto observe = MakeUserNotifications();

    HuntTheWumpus::Context gameContext{ observe, sourceOfRandom, change };
    
    try
    {
        HuntTheWumpus::Dungeon dungeon(gameContext);

        while (change.IsPlaying())
        {
            // Parse input.
            std::string input;

            std::cout << "Command? ";
            std::cout.flush();

            std::getline(std::cin, input);

            // Split into strings.
            const auto stringTokens = SplitString(input, " \t\n");

            // UI fault 1: user input delimiter characters or invalid commands
            try
            {
                HuntTheWumpus::assert(!stringTokens.empty(), __FILE__, __LINE__);

                HuntTheWumpus::assert(std::ranges::any_of(validCommands, [&stringTokens](const auto& command)
                    {
                        return stringTokens[0] == command;
                    })
                    , __FILE__, __LINE__);
            }
            catch (const std::runtime_error& e)
            {
                std::string errorMessage = "\nInvalid input.\nEnter \"m\", \"M\", \"move\", or \"MOVE\" for move command.\nEnter \"s\", \"S\", \"shoot\", or \"SHOOT\" for shoot command.\n"
                    "Move and shoot command must be followed be followed by destination cave id (move) or list of cave ids (shoot).\n"
                    "Enter \"q\", \"quit\", \"e\", \"exit\", or \"x\" to quit program.";
                std::cout << e.what() << errorMessage << std::endl;
                continue;
            }

            const auto& command = stringTokens[0];

            if (command == "m" || command == "M" || command == "move" || command == "MOVE")
            {
                try
                {
                    HuntTheWumpus::assert(stringTokens.size() >= 2, __FILE__, __LINE__);
                }
                catch (const std::runtime_error& e)
                {
                    std::string errorMessage = "\nA Move command must be followed by the destination cave id.";
                    std::cout << e.what() << errorMessage << std::endl;
                    continue;
                }

                // UI fault 2: user input non-integer value as destination cave id
                try 
                {
                    // Second token is a destination.
                    const auto destCave = std::stoi(stringTokens[1]);
                    dungeon.MakeMove(HuntTheWumpus::DungeonMove::Move, { destCave });
                }
                catch (const std::invalid_argument&)
                {
                    std::cout << "ERROR: \"" << stringTokens[1] << "\" is an invalid destination cave id. Must be an integer value!" << std::endl;
                }

            }

            if (command == "s" || command == "S" || command == "shoot" || command == "SHOOT")
            {
                try
                {
                    HuntTheWumpus::assert(stringTokens.size() >= 2, __FILE__, __LINE__);
                }
                catch (const std::runtime_error& e)
                {
                    std::string errorMessage = "\nA Shoot command must be followed by a list of caves for the arrow to go through.";
                    std::cout << e.what() << errorMessage << std::endl;
                    continue;
                }

                // Remaining tokens is the desired arrow path.
	            std::vector<int> path;
                auto firstToken = false;

                // UI fault 3: user input non-integer value(s) in list of caves
                // Provide try-catch block outside of for-loop in lieu of locally at path.push_back
                // because MakeMove is designed to throw std::invalid_argument if path vector resize
                // is omitted
                try
                {
                    for (auto&& token : stringTokens)
                    {
                        if (!firstToken)
                        {
                            firstToken = true;
                            continue;
                        }
                        path.push_back(std::stoi(token));

                    }
                    path.resize(std::min(path.size(), static_cast<size_t>(5)));
                    dungeon.MakeMove(HuntTheWumpus::DungeonMove::Shoot, path);
                }
                catch (const std::invalid_argument& e)
                {
                    // Handles error due to invalid vector entry or empty vector (thrown from MakeMove())
                    std::cout << e.what() << std::endl;
                }

            }

            if (command == "q" || command == "quit" || command == "e" || command == "exit" || command == "x")
            {
                std::cout << "Exiting." << std::endl;
                change.GameOver(false);
            }
        }
    }
    catch (const std::out_of_range& e)
    {
        // Missing notification
        std::cout << e.what() << std::endl;
        return 1; // Return non-zero status code to indicate program error
    }
    catch (const std::bad_function_call& e)
    {
        // Notification callback defined improperly
        std::cout << e.what() << std::endl;
        return 2; // Return non-zero status code to indicate program error
    }

    return 0;
}
