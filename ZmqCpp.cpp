// ZmqCpp.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <zmq.h>

struct COORDINATE{
	int x;
	int y;
	int z;
	int u;
	int v;
	int w;
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
		// // buffer
		// zmq_send(publisher, "Hello", 5, 0);

		//coord1->x = 0x89; coord1->y = 0x45; coord1->z = 0x23;
		coord1->x = 10; coord1->y = 20; coord1->z = 30; coord1->u = 40; coord1->v = 50; coord1->w = 60;
		coord2->x = 20; coord2->y = 30;

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

