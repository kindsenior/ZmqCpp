// ZmqCpp.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include <zmq.h>


int _tmain(int argc, _TCHAR* argv[])
{
	// 0MQ�̏�����
	void *context = zmq_ctx_new();


	// �N���C�A���g�p�\�P�b�g�̍쐬�Ə�����
	void *requester = zmq_socket(context, ZMQ_REQ);
	zmq_connect(requester, "tcp://192.168.97.146:5555");

	// ���M����
	zmq_send(requester, "Hello", 5, 0);

	// ��M����
	char buffer[10];
	zmq_recv(requester, buffer, 10, 0);
	printf("%c\n", buffer[0]);


	return 0;
}

