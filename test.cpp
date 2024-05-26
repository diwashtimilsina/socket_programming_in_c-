#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <regex>
#include <ctime>

using namespace std;

// Function to validate a URL using regular expressions
bool isValidURL(const string &url) {
    // Regular expression pattern for basic URL validation
    const regex urlRegex("([a-zA-Z0-9.-]+)\\.([a-zA-Z]{2,6})(:[0-9]+)?(/[a-zA-Z0-9_.-]*)*$");

    return regex_match(url, urlRegex);
}

// Function to resolve a hostname to an IP address
bool resolveHostname(const string& hostname, string& ip_address) {
    struct hostent *he;
    struct in_addr **addr_list;

    he = gethostbyname(hostname.c_str());
    if (he == NULL) {
        return false;
    }

    addr_list = (struct in_addr **) he->h_addr_list;
    ip_address = inet_ntoa(*addr_list[0]);

    return true;
}

int main() {
    string host;
    int PORT[] = {21, 22, 23, 25, 53, 80, 110, 143, 443, 587, 993, 995};
    struct timeval timeout;
    timeout.tv_sec = 2; // Timeout set to 2 seconds
    timeout.tv_usec = 0;

    // Input host URL from user
    cout << "Enter host URL: ";
    cin >> host;

    // Validate URL
    if (!isValidURL(host)) {
        cout << "Invalid URL" << endl;
        return 1;
    }

    string ipAddress;

    // Resolve hostname to IP address
    if (!resolveHostname(host, ipAddress)) {
        cout << "Failed to resolve hostname" << endl;
        return 1;
    }

    cout << "IP address of " << host << " is: " << ipAddress << endl;

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ipAddress.c_str());

    int nSocket, n;

    // Iterate over predefined ports and check if they are open
    for (int i = 0; i < sizeof(PORT) / sizeof(PORT[0]); i++) {
        // Create socket
        nSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (nSocket == -1) {
            cout << "Socket not created" << endl;
            return 1;
        }

        // Set socket timeout
        if (setsockopt(nSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
            cout << "Failed to set socket timeout" << endl;
            return 1;
        }

        server.sin_port = htons(PORT[i]);

        // Connect to the server
        n = connect(nSocket, (struct sockaddr *)&server, sizeof(server));
        if (n == 0) {
            cout << "Port " << PORT[i] << " is open" << endl;
        } else {
            cout << "Port " << PORT[i] << " is closed" << endl;
        }

        // Close the socket
        close(nSocket);
    }

    return 0;
}

