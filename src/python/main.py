import random
import os

from Player import Player



CLEAR = "cls" if os.name == "nt" else "clear"

def clear_screen() -> None:
    if CLEAR:
        import subprocess
        subprocess.run(CLEAR, shell=True)

def read_int() -> int:
    try:
        return int(input().strip())
    except ValueError:
        return -1  # Invalid input falls through to the default case

def randomEvent(p: Player) -> None:
    event = random.randint(0, 4)

    if event == 0:
        print("You found a small gift! Money +10, Happiness +5")
        p.money += 10
        p.happiness += 5

    elif event == 1:
        print("You caught a cold. Health -10, Happiness -5")
        p.health -= 10
        p.happiness -= 5

    elif event == 2:
        print("Your friend invited you out. Social +10, Happiness +10, Money -5")
        p.social += 10
        p.happiness += 10
        p.money -= 5

    elif event == 3:
        print("Unexpected car repair! Money -20, Happiness -5")
        p.money -= 20
        p.happiness -= 5

    elif event == 4:
        print("You exercised and ate healthy today. Health +10, Happiness +5")
        p.health += 10
        p.happiness += 5

    if p.health > 100: p.health = 100
    if p.happiness > 100: p.happiness = 100
    if p.social > 100: p.social = 100

    if p.health < 0: p.health = 0
    if p.happiness < 0: p.happiness = 0
    if p.social < 0: p.social = 0

def choose_action(p: Player) -> None:
    print("\nWhat do you want to do today?")
    print("1. Work\n2. Relax\n3. Exercise\n4. Socialize\n5. Look for a job")
    choice = read_int()

    if choice == 1:
        clear_screen()
        if p.job == "Unemployed":
            print("You are unemployed, cannot work.")
        else:
            print("You worked at your job. Money +50, Happiness -10, Health -5")
            p.money += 50
            p.happiness -= 10
            p.health -= 5

    elif choice == 2:
        clear_screen()
        print("You relaxed. Happiness +15, Health +5")
        p.happiness += 15
        p.health += 5
        p.social -= 5

    elif choice == 3:
        clear_screen()
        print("You exercised. Health +15, Happiness +5")
        p.health += 15
        p.happiness += 5

    elif choice == 4:
        clear_screen()
        print("You socialized. Social +20, Happiness +10, Money -10")
        p.social += 20
        p.happiness += 10
        p.money -= 10

    elif choice == 5:
        clear_screen()
        print("Choose a job:\n1. Engineer (Money +70/day)\n"
              "2. Artist (Money +30/day, Happiness +10)\n"
              "3. Teacher (Money +40/day, Social +10)")
        job_choice = read_int()
        if job_choice == 1:
            p.job = "Engineer"
        elif job_choice == 2:
            p.job = "Artist"
        elif job_choice == 3:
            p.job = "Teacher"
        else:
            print("Invalid choice.")

    elif choice == 6:
        clear_screen()
        if not p.ownsHouse and p.money >= 100:
            print("You bought a house! Money -100, Happiness +20")
            p.ownsHouse = True
            p.money -= 100
            p.happiness += 20
        elif p.ownsHouse:
            print("You already own a house.")
        else:
            print("Not enough money to buy a house.")

    elif choice == 7:
        clear_screen()
        if p.married:
            print("You had a child! Happiness +20, Social +10, Money -20")
            p.children += 1
            p.happiness += 20
            p.social += 10
            p.money -= 20
        else:
            print("You must be married to have a child.")

    else:
        clear_screen()
        print("You did nothing today.")

    # Keep stats in bounds
    p.health = min(p.health, 100)
    p.happiness = min(p.happiness, 100)
    p.social = min(p.social, 100)
    p.health = max(p.health, 0)
    p.happiness = max(p.happiness, 0)
    p.social = max(p.social, 0)

def main() -> None:
    name = input("Enter your name: ")
    player = Player(name)
    choose_action(player)

    while player.isAlive() and player.age <= 100:
        player.showStatus()
        randomEvent(player)
        choose_action(player)

        if player.age >= 65 and not player.retired:
            print("You have reached retirement age. You are now retired.")

        player.age += 1

    print(f"\nGame Over! {player.name} lived until age {player.age}.")
    print(f"Final stats: Happiness {player.happiness}, Health {player.health}, money ${player.money}, social {player.social}, Children: {player.children}, House: {"Yes" if player.ownsHouse else "No"}")


if __name__ == "__main__":
    main()