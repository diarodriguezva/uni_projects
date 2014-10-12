package de.tum.i6.cogsys.srvs;

import org.ros.exception.RemoteException;
import org.ros.exception.ServiceNotFoundException;
import org.ros.node.ConnectedNode;
import org.ros.node.service.ServiceClient;
import org.ros.node.service.ServiceResponseListener;
import org.smerobotics.util.srv.ServiceRequestBuilderFactory;

import robot_control_srvs.MoveToCS;
import robot_control_srvs.MoveToCSRequest;
import robot_control_srvs.MoveToCSResponse;

public abstract class MoveToCSRequestBuilderFactory extends ServiceRequestBuilderFactory {

	public final String SERVICE_NAME_MOVE_TO_CS = getServiceName();
	
	private ServiceClient<MoveToCSRequest, MoveToCSResponse> clientMoveToCS;

	private final Object sync = new Object();
	private volatile boolean responsePending = false;

	private boolean ok = false;
	
	public abstract String getServiceName();
	
	@Override
	public synchronized void addServiceClients(ConnectedNode connectedNode) {

		if (clientMoveToCS == null) {

			boolean found = false;

			while (!found) {

				try {

					clientMoveToCS = connectedNode.newServiceClient(
							SERVICE_NAME_MOVE_TO_CS,
							MoveToCS._TYPE);

					found = true;

					System.out.println("    Found service '"
							+ SERVICE_NAME_MOVE_TO_CS
							+ "'. (type: "
							+ MoveToCS._TYPE + ")");

				} catch (ServiceNotFoundException e) {

					System.out.println("  Waiting for service '"
							+ SERVICE_NAME_MOVE_TO_CS
							+ "' to start up. (type: "
							+ MoveToCS._TYPE + ")");

					try {
						Thread.sleep(3000);
					} catch (InterruptedException ie) {
					}

				}

			}

		}

	}

	@Override
	public synchronized void removeServiceClients() {

		if (clientMoveToCS != null) {

			clientMoveToCS.shutdown();
			clientMoveToCS = null;

			System.out.println("  Shutdown service client '"
					+ SERVICE_NAME_MOVE_TO_CS
					+ "'. (type: "
					+ MoveToCS._TYPE + ")");

		}

	}

	public boolean call(String endEffector, float x, float y, float z) {

		boolean success = false;

		MoveToCSRequest req = clientMoveToCS.newMessage();
		req.setEffector(endEffector);
		req.setX(x);
		req.setY(y);
		req.setZ(z);

		synchronized (sync) {

			responsePending = true;

			clientMoveToCS.call(req, new ServiceResponseListener<MoveToCSResponse>() {

				@Override
				public void onSuccess(MoveToCSResponse response) {

					synchronized (sync) {
						ok = response.getSuccess();
						responsePending = false;
						sync.notifyAll();
					}

				}

				@Override
				public void onFailure(RemoteException e) {

					synchronized (sync) {
						ok = false;
						responsePending = false;
						sync.notifyAll();
					}

				}

			});

			while (responsePending) {
				try {
					sync.wait();
				} catch (InterruptedException e1) {
				}
			}

			success = ok;

		}

		return success;

	}

}
