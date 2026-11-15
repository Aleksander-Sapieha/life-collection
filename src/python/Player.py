class Player:
    def __init__(self, name: str):
        self.name: str = name
        self.age: int = 18
        self.health: int = 100
        self.happiness: int = 50
        self.money: int = 100
        self.social: int = 50
        self.job: str = "Unemployed"
        self.married: bool = False
        self.children: int = 0
        self.ownsHouse: bool = False
        self.retired: bool = False

    def showStatus(self) -> None:
        print("\n Status:")
        print(f"Name: {self.name}")
        print(f"Age: {self.age}")
        print(f"Health: {self.health}")
        print(f"Happiness: {self.happiness}")
        print(f"Money: {self.money}")
        print(f"Social: {self.social}")
        print(f"Job: {self.job}")
        print(f"Married: {"Yes" if self.married else "No"}")
        print(f"Owns House: {"Yes" if self.ownsHouse else "No"}")
        print(f"Retired: {"Yes" if self.retired else "No"}")

    def isAlive(self) -> bool:
        return self.health > 0 and self.happiness > 0