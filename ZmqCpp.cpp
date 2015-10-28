// ZmqCpp.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <zmq.h>


int _tmain(int argc, _TCHAR* argv[])
{
	// 0MQの初期化
	void *context = zmq_ctx_new();


	// クライアント用ソケットの作成と初期化
	void *requester = zmq_socket(context, ZMQ_REQ);
	zmq_connect(requester, "tcp://192.168.97.146:5555");

	// 送信する
	zmq_send(requester, "Hello", 5, 0);

	// 受信する
	char buffer[10];
	zmq_recv(requester, buffer, 10, 0);
	printf("%c\n", buffer[0]);


	return 0;
}

