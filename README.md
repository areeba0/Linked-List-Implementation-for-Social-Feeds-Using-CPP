# Dynamic Post Tracker: Linked List Implementation for Social Feeds in C++
This C++ mini-program simulates a social media feed using a linked list structure. It allows users to perform various operations such as adding posts, searching posts by content, editing posts, deleting posts, and displaying posts in chronological or reverse chronological order.

# Dependencies:
This program relies on standard C++ libraries such as iostream, string, ctime, and iomanip.

# Features:
- Add Post: Users can add posts to the feed. Posts are automatically timestamped upon creation.
- Search Posts: Users can search for posts containing specific text and perform actions like liking, sharing, commenting, saving, or skipping.
- Edit Post: Users can edit the content of a post given its unique ID.
- Delete Post: Users can delete a post by providing its ID.
- Display Posts: Posts can be displayed either in chronological order (oldest first) or reverse chronological order (latest first).
- 
# Implementations:
- Post Struct: Represents each post with attributes like ID, text content, timestamp, and a pointer to the next post.
- Feed Struct: Manages the collection of posts using a linked list structure. It includes methods for adding, searching, editing, deleting, and displaying posts.
- Main Function: Implements a menu-driven interface allowing users to interact with the feed, perform operations, and display results.
  
# Usage:
- Upon running the program, a menu is presented to the user with options to search for posts, edit posts, display posts, delete posts, or exit the program.
- Users can input their choices and follow prompts to execute operations on the social media feed.
- 
# Example Scenario:
- Adding Posts: Initial posts are created upon starting the program.
- Searching Posts: Users can search for posts containing specific keywords.
- Editing Posts: Post content can be edited with updated timestamps.
- Deleting Posts: Posts can be deleted by specifying their IDs.
- Displaying Posts: Posts are displayed in chronological or reverse chronological order based on user preference.
