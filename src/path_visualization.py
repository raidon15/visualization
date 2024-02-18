import csv
import rclpy
from geometry_msgs.msg import PoseStamped
from nav_msgs.msg import Path

def read_csv(file_path):
    positions = []
    with open(file_path, 'r') as csvfile:
        csvreader = csv.reader(csvfile)
        for row in csvreader:
            try:
                x, y, z = map(float, row)
                positions.append((x, y, z))
            except ValueError as e:
                print(f"Error parsing row {row}: {e}")
    return positions

def create_path_message(positions):
    path_msg = Path()
    path_msg.header.stamp = rclpy.clock.Clock().now().to_msg()
    path_msg.header.frame_id = 'world'  # Set your desired frame_id

    for x, y, z in positions:
        pose = PoseStamped()
        pose.pose.position.x = x
        pose.pose.position.y = y
        pose.pose.position.z = z
        # You can set orientation if needed: pose.pose.orientation.x = ..., pose.pose.orientation.y = ..., ...

        # Append the pose to the path
        path_msg.poses.append(pose)

    return path_msg

def main():
    rclpy.init()
    node = rclpy.create_node('csv_to_path_node')

    file_path = 'agent_trajectory_path.csv'  # Replace with your actual CSV file path
    positions1 = read_csv('agent_trajectory_path.csv' )
    positions2 = read_csv('ideal_trajectory.csv')
    positions3 = read_csv('random.csv')
    path_msg1 = create_path_message(positions1)
    path_msg2 = create_path_message(positions2)
    path_msg3 = create_path_message(positions3)

    # Publish the path message
    path_publisher = node.create_publisher(Path, '/path_topic', 10)  # Replace 'path_topic' with your desired topic name
    path_publisher.publish(path_msg1)
    path_publisher.publish(path_msg2)
    path_publisher.publish(path_msg3)

    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
