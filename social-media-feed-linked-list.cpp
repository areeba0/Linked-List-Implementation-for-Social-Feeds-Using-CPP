#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;
// A structure shows one post
struct Post_ 
{
    //a static counter to give unique IDs to the posts
    static int ID_counter; 
    int ID;  
    // contents the text content in a string of the post
    string text_content; 
    // pointer to point the next post
    // in the fee
    Post_* Next;  
    // timestamp to show when the post was created
    time_t time_stamp;     
    
    // Constructor 
    Post_(const string& text)
        : ID(++ID_counter), text_content(text), Next(nullptr) 
    {
        time_stamp = time(nullptr); 
        // Setting the time_stamp to the current time
    }

    // Function to update the timestamp of post
    // we update the time_stamp using the editting part 
    void Update_Timestamp() 
    {
        time_stamp = time(nullptr);
    }
};
// intializing to 0 and counting the static ID_counter
int Post_::ID_counter = 0;
// A structure to show The feed of posts
struct Feed_
{
    // a pointer pointing to the head of the post linked list
    Post_* head;

    // Constructor 
    // intialize with null the empty feed
    Feed_()
    {
        head = nullptr;
    }

    // Destructor 
    ~Feed_() 
    {
        do  {
            // free memory/delete the feed obj w=after it is destroyed
              Post_* temp = head;
              head = head->Next;
              delete temp;
            } while (head);
    }
// Function to add a new post to the feed-------------------------------------------------------------------------------
    // keeping the post in the feed sorted
    // using time_stamp
    void Add_Post(const string& text)
    {
        // Create a new post with the text content avaliable
        Post_* new_post = new Post_(text);

       
        if (!head || head->time_stamp <= new_post->time_stamp)
        {
 
            // insert the new post at the beginning of the feed
            // setting the new_post's next pointer to the head
            // the current head
            new_post->Next = head; 
            // update the head to point to the new_post
            head = new_post;       
        }
        // If the feed is not empty
         // and the new post is older than the current head
        else 
        {
            Post_* cur = head; // Start with the cur(current) post as the head

            do {
                if (cur->Next && cur->Next->time_stamp > new_post->time_stamp) 
                {
                    new_post->Next = cur->Next; 
                    cur->Next = new_post;       
                    return;                       
                }
                else if (!cur->Next) 
                {
                    cur->Next = new_post; 
                    return;                  
                }
                cur = cur->Next; 
            } while (cur); 
        }
    }

 // Function to search for posts -----------------------------------------------------------------------------------------------
    // using the text content of that post
    void Search_Posts(const string& search_text_content)
    {
        Post_* cur = head; 
        // Starting with the first post in the feed
        bool found_text = false; 
        // A bool to show if the text was found in the feed of posts

        do {
            if (cur->text_content.find(search_text_content) != string::npos)
            {
      // Print info about the matching post,
                cout << "ID: " << cur->ID << "\n Text: " << cur->text_content << "\n Timestamp: " << asctime(localtime(&cur->time_stamp));
                found_text = true; 
            }
            cur = cur->Next; 
        } while (cur); 

        if (!found_text)
        {
            cout << "No posts containing \"" << search_text_content << "\" were found in the feed." << endl;
        }
        else
        {
            int matchingPost_count= 0; 
            cur = head; 

            do 
            {
                if (cur->text_content.find(search_text_content) != string::npos)
                {
                    matchingPost_count++;
                }
                cur = cur->Next; 
            } while (cur); 
            if (matchingPost_count == 1)
            {
               
                cout << "Found a single 1 post from the feed containing '" << search_text_content << "'." << endl;
            }
            else if (matchingPost_count > 1)
            {
               
                cout << "Found " << matchingPost_count << " posts containing '" << search_text_content << "'." << endl;
            }

            cout << "Do you want to perform any action on these posts?" << endl;
            cout << "\n";
            cout << "====================" << endl;
            cout << "1. Like" << endl;
            cout << "2. Share" << endl;
            cout << "3. Comment" << endl;
            cout << "4. Save" << endl;
            cout << "5. Skip" << endl;
            cout << "====================" << endl;

            int choice;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) 
            {
            case 1:
                cout << "You liked the posts." << endl;
                break;
            case 2:
                cout << "You shared on the posts." << endl;
                break;
            case 3:
                cout << "You commented the posts." << endl;
                break;
            case 4:
                cout << "You saved the posts." << endl;
                break;
            case 5:
                cout << "You skipped the posts." << std::endl;
                break;
            default:
                cout << "Error! Invalid choice." << std::endl;
            }
        }
    }
// Function to delete a post with a ID given by the user input----------------------------------------------------------------
    void Delete_Post(int id)
    {
        if (!head)
        {
            cout << "Feed is empty. No posts avaliable to  delete." << endl;
            return;
        }

        if (head->ID == id) 
        {
            Post_* temp = head; 
            head = head->Next; 
            // Updating the pointer of the head of linked list to point to the next post
            time_t deleting_tsp = temp->time_stamp;
            cout << "Post with ID " << id << " and Text = \" " << temp->text_content << "\"  has been deleted by user at Timestamp : " << asctime(localtime(&deleting_tsp)) << endl;
            delete temp; 
            // Delete the post
            return; 
        }
        Post_* cur = head;
        do 
        {
            if (cur->Next->ID == id) 
            {
               
                Post_* temp = cur->Next; 
                cur->Next = cur->Next->Next; 
                time_t deleting_tsp= temp->time_stamp;
               
                cout << "Post with ID " << id <<  " and Text = \" " << temp->text_content << "\" has been deleted by user at Timestamp : " << asctime(localtime(&deleting_tsp)) << endl;
                delete temp; // Delete the post
                return; // Exit the function
            }
            cur = cur->Next;
        } while (cur->Next); 

        cout << "Post with ID " << id << " not found" << endl;
    }
 // Recursive function to display posts in feed  in chronological order----------------------------------------------------------
    void DisplayPostsChrono(Post_* cur)
    {
        if (!cur) 
        {
            return; // if end of the list , no recursion will occur
        }

        // Recursively call 
        DisplayPostsChrono(cur->Next);
        cout << "ID = " << cur->ID << "- Text = " << cur->text_content << " - Timestamp: " << asctime(localtime(&cur->time_stamp));
    }

    // Function to display posts either in chrono or reverse chrono order
    void Display_Posts(bool latest_First)
    {
        if (!head)
        {
            cout << "Feed is empty.No post avaliable" << endl;
            return;
        }

        cout << "Displaying all Posts in the feed ";

        if (latest_First)
        {
            cout << "in reverse chrono order (Latest first, Oldest last):" << endl;
            Post_* cur = head;
            while (cur) 
            {
                cout << "ID: " << cur->ID<< " - Text: " << cur->text_content << " - Timestamp: " << asctime(localtime(&cur->time_stamp));
                cur = cur->Next; // Move to the next post in the feed
            }
        }
        else if (!latest_First)
        {
            cout << "in chronological order (Oldest first , Latest last):" << endl;
            DisplayPostsChrono(head); 
        }
    }
 // Function to edit a post with a given ID  ----------------------------------------------------------------------------
    void Edit_Post(int id, const string& new_text_content)
    {
        Post_* cur = head;
        bool found_Post = false;
        do {
            if (cur->ID == id)
            {

                string old_text_content = cur->text_content;
                cur->text_content = new_text_content;
                cur->Update_Timestamp();
                found_Post = true;


                cout << "Post with ID " << id << " has been edited successfully!!" << endl;
                cout << "Old Text: " << old_text_content<< endl;
                cout << "New Text: " << cur->text_content << endl;

                break;
            }
            else if (cur->ID < id)
            {

                cout << "Post with ID " << id << " not found." << endl;
                cout << "No edits to the post will be made since no post of that ID or text exist/ is avaliable" << endl;
                return;
            }
            cur = cur->Next;
        } while (cur);

        if (!found_Post)
        {
            cout << "Post with ID " << id << " not found." << endl;
        }
    }


};


int main()
{
    cout << "====================================================\n" << endl;
    cout << "      **SOCIAL MEDIA FEED LINKED LIST**             \n " << endl;
    cout << "====================================================" << endl;
    Feed_ obj;
    // Adding some initial posts
    obj.Add_Post("Hello World!");
    obj.Add_Post("How is everyone doing today");

    cout << "Created initial posts." << endl;
    cout << "Display intial 2 post" << endl;
    obj.Display_Posts(false);  

    int i = 0;
    while (i < 6)
    {
        string rand_text= "Random Post " + to_string(i + 1);
        obj.Add_Post(rand_text);
        cout << "Created Post: " << rand_text << endl;
        i++;
    }

    cout << "Created random posts." << endl;

    obj.Add_Post("I should be going, see you guys later.");
    obj.Add_Post("Bye");

    cout << "Added more posts." << endl;

    int choice_;
    do {
        cout << "\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "|           Menu            |" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "| 1. Search for posts.      |" << endl;
        cout << "| 2. Edit a post.           |" << endl;
        cout << "| 3. Display posts (chrono).|" << endl;
        cout << "| 4. Delete posts.          |" << endl;
        cout << "| 5. Display posts (reverse)|" << endl;
        cout << "| 6. Exit.                  |" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Enter your choice from menu: ";
        cin >> choice_;

        switch (choice_)
        {
        case 1: 
        {
           
            string search_text;
            cout << "Enter search text content from the post you have created : ";
            cin.ignore();
            getline(cin, search_text);
            cout << "Searching for posts containing '" << search_text << "~~~~~~ =" << endl;
            obj.Search_Posts(search_text);
            break;
        }
        case 2: 
        {
            int ID;
            string new_text;
            cout << "Enter the ID of the post you want to edit the text of : ";
            cin >> ID;
            cout << "Enter the new text: ";
            cin.ignore();
            getline(cin, new_text);
            obj.Edit_Post(ID, new_text);
            cout << "Post with ID " << ID << " has been edited successfully." << endl;
            break;
        }
        case 3:
        {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "| Displaying all posts in   |" << endl;
            cout << "| chrono   order            |" << endl;
            cout << "| (Oldest first)            |" << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            obj.Display_Posts(false);
            break;
        }
        case 4:
        {
            int id_post;
            cout << "Enter the ID of the post from the user , you want to delete: ";
            cin >> id_post;
            obj.Delete_Post(id_post);
            cout << "Deleted post with ID " << id_post << "." << endl;
            break;
        }
        case 5:
        {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "| Displaying all posts in   |" << endl;
            cout << "| reverse chrono            |" << endl;
            cout << "| order (Latest first)      |" << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            obj.Display_Posts(true);
            break;
        }
        case 6:
            cout << "Exiting program ~~~~" << endl;
            break;
        default:
            cout << "Error!! Invalid choice. Please enter a valid option from the menu." << endl;
        }
    } while (choice_ != 6);


    
    return 0;
}
