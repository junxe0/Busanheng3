#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ��������
#define LEN_MIN				15
#define LEN_MAX				50
// Ȯ��
#define PROB_MIN			10
#define PROB_MAX			90
// ��׷� ����
#define AGGRO_MIN			0
#define AGGRO_MAX			5
// ������ ���� ���
#define ATK_NONE			0
#define ATK_CITIZEN			1
#define ATK_DONGSEOK		2
// ������ �̵� ����
#define MOVE_LEFT			1
#define MOVE_STAY			0
// ������ ü��
#define STM_MIN				0
#define STM_MAX				5
// ������ �ൿ
#define ACTION_REST			0
#define ACTION_PROVOKE		1
#define ACTION_PULL			2

void intro(void);
int trainlength_input(void);
int percent_input(void);
int stm_inpput(void);
void start_msg(void);
void count_line(int);
void train_box(int, int, int, int, int, int, int, int, int, int);
void train_box2(int, int, int, int);
void train_box3(int, int, int, int, int);
void train_box4(int, int, int, int, int, int, int);
void train_box5(int, int, int, int, int, int, int);
int c_moveAll(int, int, int, int*, int*);
int c_move(int, int, int, int*, int*);
int c_aggroMinMax(int);
int z_move(int, int, int, int, int, int, int, int*, int*);
int z_movewhere(int, int, int, int, int, int*);
void moveresult(int, int, int, int, int, int, int, int);
void c_moveresult(int, int, int, int, int);
void z_moveresult(int, int, int);
int m_moveAll(int, int, int, int*, int*);
int m_move_inpput(int, int);
int m_movef(int, int, int, int*, int*);
int m_aggroMinMax(int);
void m_moveresult(int, int, int, int, int);
int c_action(int, int);
int z_action(int, int, int, int, int, int, int, int, int*, int*, int*);
int z_who_atk(int, int, int, int, int, int*, int*, int*);
int z_who_atk2(int, int, int, int, int, int, int*, int*);
void ATK_f(int, int, int, int, int, int);
int m_actionAll(int, int, int, int, int, int, int, int*, int*, int*);
int m_action_inpput(int, int);
int m_actionf(int, int, int, int, int, int, int*, int*, int*);
int m_pull(int, int, int, int*);
int m_stmMinMax(int);
int m_actionmsg(int, int, int, int, int, int);
void czm_repos(int, int, int, int, int, int*, int*, int*);

int main(void) {
	intro(); // �ܼ�â �̸� ����

	int train_length, p, stm, bstm = 0, count = 0, zombie = 0;
	train_length = trainlength_input(); // ���� ���� �Է�
	p = percent_input(); // �ۼ�Ʈ �Է�
	stm = stm_inpput(); // ü�� �Է�

	start_msg(); // ���� �޼��� ���

	srand((unsigned int)time(NULL)); // ���� �ʱ�ȭ

	int c_pos = train_length - 5; // �ù� �ʱ� ��ġ
	int c2_pos = train_length / 2; // �ù� 2 �ʱ� ��ġ
	int c3_pos = train_length / 4; // �ù� 3 �ʱ� ��ġ
	int v_pos = train_length - 4; // ���� �ʱ� ��ġ
	int z_pos = train_length - 2; // ���� �ʱ� ��ġ
	int m_pos = train_length - 1; // ������ �ʱ� ��ġ
	int stage = 1; // ��������
	int b_stage = 0;
	int c_alive = 3; // �ù� ����

	train_box(count, train_length, stage, c_alive, c3_pos, c2_pos, c_pos, v_pos, z_pos, m_pos); // ���� ����

	int c_bpos = 0, z_bpos = 0, m_bpos = 0; // �̵� �� ��ǥ

	int c_aggro = 1, m_aggro = 1; // ��׷�

	int m_move = 0, m_action = 0, m_action_f = 0; // ������ ����

	int c_result = 0, z_result = 0, ATK = 0; // �̵� ��� �� �� �� ���� Ȯ��

	int c_baggro = 0, _c_aggro = 0;
	int	_c_pos = 0;
	int	_c_alive = 0;

	int	_z_pos = 0;
	int	z_action_r = 0;
	int _zombie = 0;

	int _m_move = 0;
	int	_m_aggro = 0, m_baggro = 0;
	int	_m_pos = 0;
	int	_stm = 0;

	while (1) {
		++count, ++zombie, c_baggro = c_aggro, c_bpos = c_pos;
		c_aggro = c_moveAll(p, c_aggro, c_pos, &_c_pos, &c_result), c_pos = _c_pos, z_bpos = z_pos;
		z_result = z_move(count, zombie, m_aggro, c_aggro, c_pos, z_pos, m_pos, &_zombie, &_z_pos);
		zombie = _zombie, z_pos = _z_pos, m_bpos = m_pos, m_baggro = m_aggro;
		train_box(count, train_length, stage, c_alive, c3_pos, c2_pos, c_pos, v_pos, z_pos, m_pos);
		moveresult(c_result, c_bpos, c_pos, c_baggro, c_aggro, z_result, z_bpos, z_pos);
		m_aggro = m_moveAll(m_pos, z_pos, m_aggro, &_m_move, &_m_pos), m_move = _m_move, m_pos = _m_pos;
		train_box(count, train_length, stage, c_alive, c3_pos, c2_pos, c_pos, v_pos, z_pos, m_pos);
		m_moveresult(m_move, m_bpos, m_pos, m_baggro, m_aggro);
		b_stage = stage, bstm = stm;
		stage = c_action(c_pos, stage);
		if (b_stage != stage) { break; }
		z_action_r = z_action(z_pos, c_pos, m_pos, m_aggro, c_aggro, stm, c_alive, stage, &_stm, &ATK, &_c_alive);
		stm = _stm, c_alive = _c_alive;
		ATK_f(z_action_r, m_aggro, c_aggro, bstm, stm, ATK);
		m_action_f = m_actionAll(m_pos, z_pos, count, zombie, m_aggro, p, stm, &_zombie, &_m_aggro, &_stm);
		m_baggro = m_aggro, bstm = stm, m_aggro = _m_aggro, stm = _stm, zombie = _zombie;
		m_actionmsg(m_action_f, m_pos, m_baggro, m_aggro, bstm, stm);
		czm_repos(stage, train_length, c_pos, z_pos, m_pos, &_c_pos, &_z_pos, &_m_pos);
		c_pos = _c_pos, z_pos = _z_pos, m_pos = _m_pos;
	}
	return 0;
}

void intro() { // �ܼ� â �̸� ����
	system("title 20242397 ���ؼ� �λ��� 2");
}

int trainlength_input(void) { // ���� ���� �Է�
	int train_length;
	printf("������ ���̸� �Է����ּ���. ( %d ~ %d )\n", LEN_MIN, LEN_MAX);
	scanf_s("%d", &train_length);
	while ((train_length < LEN_MIN) || (train_length > LEN_MAX)) {
		printf("������ ���̸� �Է����ּ���. ( %d ~ %d )\n", LEN_MIN, LEN_MAX);
		scanf_s("%d", &train_length);
	}
	return train_length;
}

int percent_input(void) { // ������ Ȯ�� �Է�
	int p;
	printf("�ù��� �������� �� �� Ȯ���� �Է����ּ���. ( %d ~ %d )\n", PROB_MIN, PROB_MAX);
	scanf_s("%d", &p);
	while ((p < PROB_MIN) || (p > PROB_MAX)) {
		printf("�ù��� �������� �� �� Ȯ���� �Է����ּ���. ( %d ~ %d )\n", PROB_MIN, PROB_MAX);
		scanf_s("%d", &p);
	}
	return p;
}

int stm_inpput(void) { // ������ ���� ü�� �Է�
	int stm;
	printf("�������� ���� ü�� ���� �Է����ּ���. ( %d ~ %d )\n", STM_MIN, STM_MAX);
	scanf_s("%d", &stm);
	while ((stm < STM_MIN) || (stm > STM_MAX)) {
		printf("�������� ���� ü�� ���� �Է����ּ���. ( %d ~ %d )\n", STM_MIN, STM_MAX);
		scanf_s("%d", &stm);
	}
	return stm;
}

void start_msg(void) { // ���� ����
	printf("\n\n");
	printf(":'######::::::'###::::'##::::'##:'########:::::'######::'########::::'###::::'########::'########:'####:\n");
	printf("'##... ##::::'## ##::: ###::'###: ##.....:::::'##... ##:... ##..::::'## ##::: ##.... ##:... ##..:: ####:\n");
	printf(" ##:::..::::'##:. ##:: ####'####: ##:::::::::: ##:::..::::: ##:::::'##:. ##:: ##:::: ##:::: ##:::: ####:\n");
	printf(" ##::'####:'##:::. ##: ## ### ##: ######::::::. ######::::: ##::::'##:::. ##: ########::::: ##::::: ##::\n");
	printf(" ##::: ##:: #########: ##. #: ##: ##...::::::::..... ##:::: ##:::: #########: ##.. ##:::::: ##:::::..:::\n");
	printf(" ##::: ##:: ##.... ##: ##:.:: ##: ##::::::::::'##::: ##:::: ##:::: ##.... ##: ##::. ##::::: ##::::'####:\n");
	printf(". ######::: ##:::: ##: ##:::: ##: ########::::. ######::::: ##:::: ##:::: ##: ##:::. ##:::: ##:::: ####:\n");
	printf(":......::::..:::::..::..:::::..::........::::::......::::::..:::::..:::::..::..:::::..:::::..:::::....::\n");
	printf("\n\n");
}

void train_box(int count, int train_length, int stage, int c_alive, int c3_pos, int c2_pos, int c_pos, int v_pos, int z_pos, int m_pos) { // ���� ����
	count_line(count); // ~��°
	if (stage == 1) { train_box2(train_length, c_pos, z_pos, m_pos); }
	else if (stage == 2) { train_box3(train_length, c_pos, v_pos, z_pos, m_pos); }
	else if (stage == 3) { train_box4(train_length, c_alive, c3_pos, c2_pos, c_pos, z_pos, m_pos); }
	else if (stage == 4) { train_box5(train_length, c_alive, c3_pos, c2_pos, c_pos, z_pos, m_pos); }
}

void count_line(int count) { // ~��° ��
	if (count <= 0) {
		printf("--------------- �� �� �� �� ---------------\n");
	}
	else {
		printf("-------------- %d �� ° �� �� --------------\n", count);
	}
}

void train_box2(int train_length, int c_pos, int z_pos, int m_pos) { // ���� ����
	for (int i = 1; i <= 3; i++) {
		for (int i2 = 1; i2 <= train_length; i2++) {
			if ((i == 1) || (i == 3) || ((i == 2) & ((i2 == train_length)) || (i2 == 1))) { printf("#"); }
			else if ((i == 2) & (i2 == c_pos)) { printf("C"); }
			else if ((i == 2) & (i2 == z_pos)) { printf("Z"); }
			else if ((i == 2) & (i2 == m_pos)) { printf("M"); }
			else if (i == 2) { printf(" "); }
		}
		printf("\n");
	}
	printf("\n\n");
}

void train_box3(int train_length, int c_pos, int v_pos, int z_pos, int m_pos) { // ���� ����
	for (int i = 1; i <= 3; i++) {
		for (int i2 = 1; i2 <= train_length; i2++) {
			if ((i == 1) || (i == 3) || ((i == 2) & ((i2 == train_length)) || (i2 == 1))) { printf("#"); }
			else if ((i == 2) & (i2 == c_pos)) { printf("C"); }
			else if ((i == 2) & (i2 == v_pos)) { printf("V"); }
			else if ((i == 2) & (i2 == z_pos)) { printf("Z"); }
			else if ((i == 2) & (i2 == m_pos)) { printf("M"); }
			else if (i == 2) { printf(" "); }
		}
		printf("\n");
	}
	printf("\n\n");
}

void train_box4(int train_length, int c_alive, int c3_pos, int c2_pos, int c_pos, int z_pos, int m_pos) { // ���� ����
	for (int i = 1; i <= 3; i++) {
		for (int i2 = 1; i2 <= train_length; i2++) {
			if ((i == 1) || (i == 3) || ((i == 2) & ((i2 == train_length)) || (i2 == 1))) { printf("#"); }
			else if ((i == 2) & (i2 == c3_pos) & (c_alive == 1)) { printf("C"); }
			else if ((i == 2) & (i2 == c2_pos) & (c_alive == 2)) { printf("C"); }
			else if ((i == 2) & (i2 == c_pos) & (c_alive == 3)) { printf("C"); }
			else if ((i == 2) & (i2 == z_pos)) { printf("Z"); }
			else if ((i == 2) & (i2 == m_pos)) { printf("M"); }
			else if (i == 2) { printf(" "); }
		}
		printf("\n");
	}
	printf("\n\n");
}

void train_box5(int train_length, int c_alive, int c3_pos, int c2_pos, int c_pos, int z_pos, int m_pos) { // ���� ����
	for (int i = 1; i <= 3; i++) {
		for (int i2 = 1; i2 <= train_length; i2++) {
			if ((i == 1) || (i == 3) || ((i == 2) & ((i2 == train_length)) || (i2 == 1))) { printf("#"); }
			else if ((i == 2) & (i2 == c3_pos) & (c_alive == 1)) { printf("C"); }
			else if ((i == 2) & (i2 == c2_pos) & (c_alive == 1)) { printf("M"); }
			else if ((i == 2) & (i2 == c2_pos) & (c_alive == 2)) { printf("C"); }
			else if ((i == 2) & (i2 == c_pos) & (c_alive == 2)) { printf("M"); }
			else if ((i == 2) & (i2 == c_pos) & (c_alive == 3)) { printf("C"); }
			else if ((i == 2) & (i2 == z_pos)) { printf("Z"); }
			else if ((i == 2) & (i2 == m_pos)) { printf("M"); }
			else if (i == 2) { printf(" "); }
		}
		printf("\n");
	}
	printf("\n\n");
}

int c_moveAll(int p, int c_aggro, int c_pos, int *_c_pos, int* c_result) {
	int _c_aggro, _c_pos_;
	*c_result = c_move(p, c_aggro, c_pos, &_c_aggro, &_c_pos_); // �ù� �̵�
	*_c_pos = _c_pos_;
	return c_aggroMinMax(_c_aggro); // �ִ� �ּ� ��
}

int c_move(int p, int c_aggro, int c_pos, int* _c_aggro, int* _c_pos_) { // �ù� �̵�
	int c_per = rand() % 100 + 1;
	if (c_per <= p) {
		*_c_pos_ = c_pos; // ��ġ
		*_c_aggro = --c_aggro; // ��׷�
		return 0; // ��� ���
	}
	else if (c_per > p) {
		*_c_pos_ = c_pos - 1;
		*_c_aggro = ++c_aggro;
		return 1; // ��� ���
	}
}

int c_aggroMinMax(int _c_aggro) { // �ù� ��׷� �ּڰ� �ִ� �Ǵ�
	if (_c_aggro >= AGGRO_MAX) {
		return AGGRO_MAX; // �� ��
	}
	else if (_c_aggro <= AGGRO_MIN) {
		return AGGRO_MIN; // �ּڰ�
	}
	else {
		return _c_aggro; // ���� ��
	}
}

int z_move(int count, int zombie, int m_aggro, int c_aggro, int c_pos, int z_pos, int m_pos, int* _zombie, int* _z_pos) { // ���� �̵�
	int _z_pos_, result;
	*_zombie = zombie;
	if (count % 2 != 0) {
		if (count < zombie) {
			*_zombie = --zombie;
			*_z_pos = z_pos; // ��ġ
			result = 2; // ��� ���
		}
		else {
			result = z_movewhere(m_aggro, c_aggro, c_pos, z_pos, m_pos, &_z_pos_); // ���� �̵� ����
			*_z_pos = _z_pos_; // ���� ���� ��ġ ��ȯ
		}
	}
	else {
		*_z_pos = z_pos; // ���� ��ġ ��ȯ
		result = 1; // ��� ���
	}
	return result;
}

int z_movewhere(int m_aggro, int c_aggro, int c_pos, int z_pos, int m_pos, int* _z_pos_) { // ���� �̵� ����
	*_z_pos_ = z_pos;
	if (m_aggro <= c_aggro) {
		if (c_pos == z_pos - 1) {
			return 3;
		}
		else {
			*_z_pos_ = z_pos - 1;
			return 0;
		}
	}
	else {
		if (m_pos == z_pos + 1) {
			return 3;
		}
		else {
			*_z_pos_ = z_pos + 1;
			return 0;
		}
	}
}

void moveresult(int c_result, int c_bpos, int c_pos, int c_baggro, int c_aggro, int z_result, int z_bpos, int z_pos) {
	c_moveresult(c_result, c_bpos, c_pos, c_baggro, c_aggro); // �ù� �̵� ���
	z_moveresult(z_result, z_bpos, z_pos); // ���� �̵� ���
}

void c_moveresult(int c_result, int c_bpos, int c_pos, int c_baggro, int c_aggro) { // �ù� �̵� ��� ���
	if (c_result == 0) {
		printf("�ù� : ���ڸ� %d ( ��׷� : %d -> %d )\n", c_pos - 1, c_baggro, c_aggro);
	}
	else if (c_result == 1) {
		printf("�ù� : %d -> %d ( ��׷� : %d -> %d )\n", c_bpos - 1, c_pos - 1, c_baggro, c_aggro);
	}
}

void z_moveresult(int z_result, int z_bpos, int z_pos) { // ���� �̵� ��� ���
	if (z_result == 0) {
		printf("���� : %d -> %d\n\n", z_bpos - 1, z_pos - 1);
	}
	else if (z_result == 1) {
		printf("���� : ���ڸ� %d ( ������ �� �����ϴ�. )\n\n", z_pos - 1);
	}
	else if (z_result == 2) {
		printf("���� : ���ڸ� %d ( �ٵ�� )\n\n", z_pos - 1);
	}
	else if (z_result == 3) {
		printf("���� : ���ڸ� %d\n\n", z_pos - 1);
	}
}

int m_moveAll(int m_pos, int z_pos, int m_aggro, int* _m_move, int* _m_pos) {
	int m_move, _m_aggro, _m_pos_;
	m_move = m_move_inpput(m_pos, z_pos);
	m_movef(m_move, m_aggro, m_pos, &_m_aggro, &_m_pos_); // ������ �̵�
	*_m_move = m_move, *_m_pos = _m_pos_;
	return m_aggroMinMax(_m_aggro); // ��ȯ �� ����
}

int m_move_inpput(int m_pos, int z_pos) { // ������ �̵� ����
	int m_move;
	if (m_pos == z_pos + 1) {
		printf("�������� �̵� ���θ� �������ּ���. ( %d:stay )\n", MOVE_STAY);
		scanf_s("%d", &m_move);
		while ((m_move != MOVE_STAY)) {
			printf("�������� �̵� ���θ� �������ּ���. ( %d:stay )\n", MOVE_STAY);
			scanf_s("%d", &m_move);
		}
	}
	else {
		printf("�������� �̵� ���θ� �Է����ּ���. ( %d:stay, %d:left )\n", MOVE_STAY, MOVE_LEFT);
		scanf_s("%d", &m_move);
		while ((m_move != MOVE_STAY) && (m_move != MOVE_LEFT)) {
			printf("�������� �̵� ���θ� �Է����ּ���. ( %d:stay, %d:�̵� )\n", MOVE_STAY, MOVE_LEFT);
			scanf_s("%d", &m_move);
		}
	}
	return m_move;
}

int m_movef(int m_move, int m_aggro, int m_pos, int* _m_aggro, int* _m_pos_) {
	if (m_move == MOVE_STAY) {
		*_m_pos_ = m_pos; // ��ġ
		*_m_aggro = --m_aggro;
		return 0; // ��� ���
	}
	else if (m_move == MOVE_LEFT) {
		*_m_pos_ = m_pos - 1;
		*_m_aggro = ++m_aggro;
		return 1; // ��� ���
	}
}

int m_aggroMinMax(int _m_aggro) { // ������ ��׷� �ּڰ� �ִ� �Ǵ�
	if (_m_aggro >= AGGRO_MAX) { // �ִ�
		return AGGRO_MAX;
	}
	else if (_m_aggro <= AGGRO_MIN) { // �ּڰ�
		return AGGRO_MIN;
	}
	else {
		return _m_aggro; // ���� ��
	}
}

void m_moveresult(int m_result, int m_bpos, int m_pos, int m_baggro, int m_aggro) { // ������ �̵� ���
	if (m_result == MOVE_STAY) {
		printf("������ : ���ڸ� %d ( ��׷� : %d -> %d )\n\n", m_pos - 1, m_baggro, m_aggro);
	}
	else if (m_result == MOVE_LEFT) {
		printf("������ : %d -> %d ( ��׷� : %d -> %d )\n\n", m_bpos - 1, m_pos - 1, m_baggro, m_aggro);
	}
}

int c_action(int c_pos, int stage) { // �ù� �ൿ ���
	if (c_pos == 2) {
		if (stage < 4) {
			printf("Ż�� ����!!!\n�ù��� ���� ���������� �����մϴ�.\n");
			stage++;
		}
		else if (4 <= stage) {
			printf("You Win!!!\n�ù��� Ż�⿡ �����Ͽ����ϴ�.\n");
			exit(0);
		}
	}
	else {
		printf("�ù��� �ƹ��͵� ���� �ʾҽ��ϴ�.\n");
	}
	return stage;
}

int z_action(int z_pos, int c_pos, int m_pos, int m_aggro, int c_aggro, int stm, int c_alive, int stage, int* _stm, int* ATK, int* _c_alive) { // ���� �ൿ ���
	*_stm = stm; // ü�� ������ ���ٸ� ü�� �ٽ� ��ȯ
	int result, _stm_ = 0, _ATK = 0, _c_alive_ = 0;
	if ((c_pos == (z_pos - 1)) && (m_pos == (z_pos + 1))) {
		result = z_who_atk(m_aggro, c_aggro, stm, c_alive, stage, &_stm_, &_ATK, &_c_alive_);
		*_stm = _stm_ /* ü�� ���� */, *ATK = _ATK; /* �� �� ���� ���� */
		return result;
	}
	else if ((c_pos == (z_pos - 1)) || (m_pos == (z_pos + 1))) {
		result = z_who_atk2(c_pos, z_pos, m_pos, stm, c_alive, stage, &_stm_, &_c_alive_);
		*_stm = _stm_ /* ü�� ���� */, *ATK = 0 /* �� �� ���� ���� */, *_c_alive = _c_alive_; /* �ù� ���� ���� */
		return result;
	}
	else {
		return ATK_NONE;
	}
}

int z_who_atk(int m_aggro, int c_aggro, int stm, int c_alive, int stage, int* _stm_, int* _ATK, int* _c_alive_) {
	*_c_alive_ = c_alive;
	if (m_aggro >= c_aggro) {
		*_stm_ = --stm;
		*_ATK = 1;
		return ATK_DONGSEOK;
	}
	else {
		if (3 <= stage) {
			*_c_alive_ = --c_alive;
		}
		return ATK_CITIZEN;
	}
}

int z_who_atk2(int c_pos, int z_pos, int m_pos, int stm, int c_alive, int stage, int* _stm_, int* _c_alive_) {
	*_c_alive_ = c_alive;
	if (m_pos == (z_pos + 1)) {
		*_stm_ = --stm;
		return ATK_DONGSEOK;
	}
	else if (c_pos == (z_pos - 1)) {
		if (3 <= stage) {
			*_c_alive_ = --c_alive;
		}
		return ATK_CITIZEN;
	}
}

void ATK_f(int z_action_r, int m_aggro, int c_aggro, int bstm, int stm, int ATK) { // ������ ��� Ȯ��
	if (z_action_r == ATK_DONGSEOK) {
		if (ATK == 1) {
			printf("���� �������� �����Ͽ����ϴ�. ( %d(C) vs. %d(M), ������ ü�� : %d -> %d )\n", c_aggro, m_aggro, bstm, stm);
		}
		else {
			printf("���� �������� �����Ͽ����ϴ�. ( ������ ü�� : %d -> %d )\n", bstm, stm);
		}
		if (stm <= 0) {
			printf("GAME OVER...\n�������� ����Ͽ����ϴ�...");
			exit(0);
		}
	}
	else if (z_action_r == ATK_CITIZEN) {
		printf("GAME OVER...\n�ù��� ��Ű�µ� �����Ͽ����ϴ�...\n");
		exit(0);
	}
	else if (z_action_r == ATK_NONE) {
		printf("����� �ƹ��� �������� ���߽��ϴ�.\n");
	}
}

int m_actionAll(int m_pos, int z_pos, int count, int zombie, int m_aggro, int p, int stm, int* _zombie, int* _m_aggro, int* _stm) {
	int m_action, m_action_f, _m_aggro_, _stm_, _zombie_;
	m_action = m_action_inpput(m_pos, z_pos);
	m_action_f = m_actionf(count, zombie, m_action, m_aggro, p, stm, &_zombie_, &_m_aggro_, &_stm_);
	*_zombie = _zombie_;
	*_m_aggro = m_aggroMinMax(_m_aggro_);
	*_stm = m_stmMinMax(_stm_);
	return m_action_f;
}

int m_action_inpput(int m_pos, int z_pos) { // ������ �ൿ ����
	int m_action;
	if (m_pos == z_pos + 1) {
		printf("�������� �ൿ�� �������ּ���. ( 0:�޽�, 1:����, 2:�ٵ�� )\n");
		printf("�ٵ��� ������ ���� �ʽ��ϴ�.\n");
		scanf_s("%d", &m_action);
		while ((m_action != ACTION_REST) && (m_action != ACTION_PROVOKE) && (m_action != ACTION_PULL)) {
			printf("�������� �ൿ�� �������ּ���. ( 0:stay, 1:����, 2:�ٵ�� )\n");
			printf("�ٵ��� ������ ���� �ʽ��ϴ�.\n");
			scanf_s("%d", &m_action);
		}
	}
	else {
		printf("�������� �ൿ�� �������ּ���. ( 0:�޽�, 1:���� )\n");
		scanf_s("%d", &m_action);
		while ((m_action != ACTION_REST) && (m_action != ACTION_PROVOKE)) {
			printf("�������� �ൿ�� �������ּ���. ( 0:�޽�, 1:���� )\n");
			scanf_s("%d", &m_action);
		}
	}
	printf("\n");
	return m_action;
}

int m_actionf(int count, int zombie, int m_action, int m_aggro, int p, int stm, int* _zombie_, int* _m_aggro_, int* _stm_) { // ������ �ൿ
	int result = 0, _zom_bie_;
	if (m_action == ACTION_REST) {
		m_aggro--; /* ��׷� */
		stm++; /* ü�� */
		result = 0; /* ��� ��� */
	}
	else if (m_action == ACTION_PROVOKE) {
		m_aggro = AGGRO_MAX; /* ��׷� */
		result = 1; /* ��� ��� */
	}
	else if (m_action == ACTION_PULL) {
		m_aggro += 2; /* ��׷� */
		stm--; /* ü�� */
		result = m_pull(p, count, zombie, &_zom_bie_);
		*_zombie_ = _zom_bie_;
	}
	*_m_aggro_ = m_aggro; /* ��׷� */
	*_stm_ = stm; /* ü�� */
	*_zombie_ = zombie;
	return result;
}

int m_pull(int count, int zombie, int p, int* _zom_bie_) {
	int m_per = rand() % 100 + 1;
	if (m_per <= p) { // �ٵ�� ����
		*_zom_bie_ = zombie; /* �ٵ�� ��ȯ */
		return 2; // ��� ���
	}
	else if (m_per > p) { // �ٵ�� ����
		*_zom_bie_ = ++zombie; /* �ٵ�� ��ȯ */
		if ((zombie - count) >= 2) { // 2 �̻� ���̰� �� ���
			*_zom_bie_ = count + 1; /* �ٵ�� ��ȯ */
		}
		return 3; // ��� ���
	}
}

int m_stmMinMax(int _stm) { // ������ ü�� �ּڰ� �ִ� �Ǵ�
	if (_stm >= STM_MAX) {
		return STM_MAX; // �ִ�
	}
	else if (_stm <= STM_MIN) {
		return STM_MIN; // �ּڰ�
	}
	else {
		return _stm; // ���� ��
	}
}

int m_actionmsg(int m_action_f, int m_pos, int m_baggro, int m_aggro, int bstm, int stm) { // ������ �ൿ ���
	if (m_action_f == 0) {
		printf("�������� �޽��� ���߽��ϴ�.\n");
		printf("������ : %d ( ��׷� : %d -> %d, ü�� : %d -> %d )\n\n", m_pos - 1, m_baggro, m_aggro, bstm, stm);
	}
	else if (m_action_f == 1) {
		printf("�������� ���� �����߽��ϴ�...\n");
		printf("������ : %d ( ��׷� : %d -> %d, ü�� : %d )\n\n", m_pos - 1, m_baggro, m_aggro, stm);
	}
	else if (m_action_f == 2) {
		printf("�������� ���� �ٵ�⿡ �����߽��ϴ�...\n");
		printf("������ : %d ( ��׷� : %d -> %d, ü�� : %d -> %d )\n\n", m_pos - 1, m_baggro, m_aggro, bstm, stm);
	}
	else if (m_action_f == 3) {
		printf("�������� ���� �ٵ�⿡ �����߽��ϴ�. ����� �����Ͽ� ������ �� �����ϴ�.\n");
		printf("������ : %d ( ��׷� : %d -> %d, ü�� : %d -> %d )\n\n", m_pos - 1, m_baggro, m_aggro, bstm, stm);
	}
}

void czm_repos(int stage, int train_length, int c_pos, int z_pos, int m_pos, int *_c_pos, int *_z_pos, int *_m_pos) {
	*_c_pos = c_pos; // �ù� ��ġ ��ȯ
	*_z_pos = z_pos; // ���� ��ġ ��ȯ
	*_m_pos = m_pos; // ������ ��ġ ��ȯ
	if (2 <= stage && stage >= 4) {
		*_c_pos = train_length - 5; // �ù� �ʱ� ��ġ
		*_z_pos = train_length - 2; // ���� �ʱ� ��ġ
		*_m_pos = train_length - 1; // ������ �ʱ� ��ġ
	}
}