// ZmqCpp.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <zmq.h>
#include <string.h>

struct POINT3D{
	int x;
	int y;
	int z;
};
typedef POINT3D point;

struct COORDINATE{
	int id;
	//std::string name;
	point p;
	char name[10];
};
typedef COORDINATE coordinate;


int _tmain(int argc, _TCHAR* argv[])
{
	//// 0MQの初期化
	//void *context = zmq_ctx_new();


	//// クライアント用ソケットの作成と初期化
	//void *requester = zmq_socket(context, ZMQ_REQ);
	//zmq_connect(requester, "tcp://192.168.97.146:5555");

	//// 送信する
	//zmq_send(requester, "Hello", 5, 0);

	//// 受信する
	//char buffer[10];
	//zmq_recv(requester, buffer, 10, 0);
	//printf("%c\n", buffer[0]);


	// 0MQの初期化
	void *context = zmq_ctx_new();

	void *publisher = zmq_socket(context, ZMQ_PUB);
	// zmq_connect(publisher, "tcp://localhost:5556");// clientがconnect
	zmq_connect(publisher, "tcp://192.168.97.146:5556");// clientがconnect

	coordinate* coord1 = new coordinate;
	coordinate* coord2 = new coordinate;

	// while(1){
	for (int i = 0; i < 50000; ++i){
		coord1->id = 1;
		strcpy(coord1->name,"1234567890");
		coord1->p.x = 10; coord1->p.y = 20; coord1->p.z = 30;
		coord2->id = 2;
		strcpy(coord2->name, "arm");
		coord2->p.x = 12; coord2->p.y = 34; coord2->p.z = 56;

		// msg
		zmq_msg_t msg;
		zmq_msg_init_size(&msg, sizeof(*coord1));
		memcpy(zmq_msg_data(&msg), coord1, sizeof(*coord1));
		// zmq_msg_send(&msg, publisher, 0);
		zmq_msg_send(&msg, publisher, ZMQ_SNDMORE);
		zmq_msg_t msg1;
		zmq_msg_init_size(&msg1, sizeof(*coord2));
		memcpy(zmq_msg_data(&msg1), coord2, sizeof(*coord2));
		zmq_msg_send(&msg1, publisher, ZMQ_DONTWAIT);


	}
	free(coord1);
	free(coord2);


	return 0;
}

