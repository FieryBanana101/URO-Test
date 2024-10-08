import random
import time

class Robot:
    def __init__(self,armor, weight_type):
        self.armor = armor
        self.weight_type = weight_type

class reconRobot(Robot):
    def __init__(self,shortRangeDamage,longRangeDamage):
        super().__init__(70,"light")
        self.shortRangeDamage = shortRangeDamage
        self.longRangeDamage = longRangeDamage

class stealthRobot(Robot):
    def __init__(self,shortRangeDamage,longRangeDamage):
        super().__init__(50,"light")
        self.shortRangeDamage = shortRangeDamage
        self.longRangeDamage = longRangeDamage

class shortRangeCombatRobot(Robot):
    def __init__(self,shortRangeDamage,longRangeDamage):
        super().__init__(120,"heavy")
        self.shortRangeDamage = shortRangeDamage
        self.longRangeDamage = longRangeDamage

class longRangeCombatRobot(Robot):
    def __init__(self,shortRangeDamage,longRangeDamage):
        super().__init__(100,"heavy")
        self.shortRangeDamage = shortRangeDamage
        self.longRangeDamage = longRangeDamage

class Battle:
    def __init__(self):
        pass

    def start_fight(self, robot1, robot2):
      while True:
        if robot1.armor <= 0:
            print("You Lose!")
            break
        if robot2.armor <= 0:
            print("You win!")
            break
        print("enter 1 to do short range attack, 2 to do long range attack: ")
        choice = int(input())
        damage = robot1.shortRangeDamage
        if(choice == 2):
            damage = robot1.longRangeDamage
        time.sleep(0.5)
        print("\nyour robot attacked the enemy...")
        print(f"enemy robot receives {damage} damage")
        robot2.armor -= damage
        if robot2.armor < 0:
            robot2.armor = 0
        print(f"Your armor: {robot1.armor}")
        print(f"Enemy armor: {robot2.armor}\n")
        time.sleep(1)
        choice = random.randint(1,2)
        damage = robot2.shortRangeDamage
        if(choice == 2):
            damage = robot2.longRangeDamage
        robot1.armor -= damage
        if robot1.armor < 0:
            robot1.armor = 0
        print("\nenemy robot attacked you....")
        print(f"your robot receives {damage} damage")
        print(f"Your armor: {robot1.armor}")
        print(f"Enemy armor: {robot2.armor}\n")
        time.sleep(0.5)
        

        

class Game:
    def __init__(self, message):
       print(message)

    def add_robot(self, player_robot, enemy_robot):
        self.player_robot = player_robot
        self.enemy_robot = enemy_robot

    def start_game(self):
        battle = Battle()
        battle.start_fight(self.player_robot, self.enemy_robot)

print("Welcome to the battle of robots!")
print("Choose a robots:")
print("1.) Recon robot")
print("2.) Stealth robot")
print("3.) Short range combat robot")
print("4.) Long range combat robot")

choice = int(input(">> "))
if choice < 0:
    raise Exception("")
if choice == 1:
    player_robot = reconRobot(random.randint(20,40),random.randint(30,50))
elif choice == 2:
    player_robot = stealthRobot(random.randint(10,20),random.randint(10,20))
elif choice == 3:
     player_robot = shortRangeCombatRobot(random.randint(40,60),random.randint(20,30))
else:
    player_robot = longRangeCombatRobot(random.randint(20,30),random.randint(40,60))

enemy_choice = random.randint(1,4)

if enemy_choice == 1:
    enemy_robot = reconRobot(random.randint(20,40),random.randint(30,50))
elif enemy_choice == 2:
    enemy_robot = stealthRobot(random.randint(10,20),random.randint(10,20))
elif enemy_choice == 3:
    enemy_robot = shortRangeCombatRobot(random.randint(40,60),random.randint(20,30))
else:
    enemy_robot = longRangeCombatRobot(random.randint(20,30),random.randint(40,60))

game = Game("Let the battle begin!")

game.add_robot(player_robot,enemy_robot)
game.start_game()


